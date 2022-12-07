################################################################################
# File Name         : dashboard.py
# Description       : Contains Zephyr dashboard program which is designed to run
#                     on the central hub and provides a web interface for
#                     monitoring the vent systems.
#
# Author            : Pierino Zindel
# Creation Date     : December 05, 2022
# Last Revision     : N/A
# Version           : 1.0.0
################################################################################


# LIBRARIES
# Standard Libraries
from datetime import datetime
import json
import pathlib
import os
import socket

# 3rd Party Libraries
import dash
from dash import dcc, html, dash_table
from dash.dependencies import Input, Output, State
import dash_daq as daq
import pandas as pd
import plotly.graph_objs as go
from plotly.subplots import make_subplots

# Custom Libraries
from version import __version__


# GLOBAL VARIABLES
# Set the path to the application
APP_PATH = str(pathlib.Path(__file__).parent.resolve())
# Set the path to the configuration data file
CONFIG_FP = os.path.join(APP_PATH, "config", "vent_status_config.json")
# Set the path to the vent map (app vent name to vent address)
VENTMAP_FP = os.path.join(APP_PATH, "config", "vent_map.json")
# Set the path to the time-series data file
DATA_FP = os.path.join(APP_PATH, "data", "vent_status_log.csv")

# Set the connection address for the web socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    APP_ADDRESS = s.getsockname()[0]
except:
    APP_ADDRESS = "192.168.1.189"
APP_PORT = 8050

# Intialize the Dash application
APP = dash.Dash(
    __name__,
    meta_tags=[{"name": "viewport", "content": "width=device-width, initial-scale=1"}],
)
APP.title = "Zephyr Dashboard"
SERVER = APP.server
APP.config["suppress_callback_exceptions"] = True


# FUNCTIONS
# ===== Banner Section =====
def build_banner() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the banner
    of the web application which appears at the top of the page.
    
    Returns:
        (dash.html.Div): A division element containing the banner sub-elements.
    """
    return html.Div(
        id="banner",
        className="banner",
        children=[
            html.Div(
                id="banner-text",
                children=[
                    html.H5("Zephyr Hub Dashboard"),
                    html.H6("Vent Control and Monitoring"),
                ],
            ),
            html.Div(
                id="banner-logo",
                children=[
                    html.Button(
                        id="learn-more-button", children="ABOUT", n_clicks=0
                    ),
                    html.A(
                        html.Img(id="logo", src=APP.get_asset_url("logo.png")),
                        href="https://github.com/pzindel/capstone-project",
                    ),
                ],
            ),
        ],
    )


@APP.callback(
    Output("markdown", "style"),
    [Input("learn-more-button", "n_clicks"), Input("markdown_close", "n_clicks")],
)
def update_click_output(button_click: int, close_click: int) -> dict:
    """
    A callback function that is triggered by clicking the "ABOUT" button
    located in the banner section, or clicking the "CLOSE" button on the
    related pop-up.
    
    Alters the CSS styling of the "ABOUT" pop-up to be visible when the button
    is clicked and invisible when closed.
    
    Parameters:
        button_click (int): The number of times the open button has been clicked.
        close_click (int): The number of times the close button has been pressed.
    
    Returns:
        (dict): A CSS styling dictionary.
    """
    ctx = dash.callback_context

    # Check if the open button triggered the callback
    if ctx.triggered:
        prop_id = ctx.triggered[0]["prop_id"].split(".")[0]
        if prop_id == "learn-more-button":
            # Make the pop-up visible
            return {"display": "block"}

    # Make the pop-up invisible
    return {"display": "none"}


def generate_modal() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the contents
    of the "ABOUT" pop-up which appears in the webpage banner.
    
    Returns:
        (dash.html.Div): A division element containing the 'about' details.
    """
    return html.Div(
        id="markdown",
        className="modal",
        children=(
            html.Div(
                id="markdown-container",
                className="markdown-container",
                children=[
                    html.Div(
                        className="close-container",
                        children=html.Button(
                            "Close",
                            id="markdown_close",
                            n_clicks=0,
                            className="closeButton",
                        ),
                    ),
                    html.Div(
                        className="markdown-text",
                        children=dcc.Markdown(
                            children=(
                                """
                        ###### What is this dashboard for?

                        This dashboard provides a interface for monitoring and
                        updating your Zephyr Vents in real-time.

                        ###### What does this app show?

                        The dashboad provides three tabs which display different
                        levels of information about the connected vents. 

                        The "FLOOR PLANS" tab gives a simple overview of the
                        vents in your home and their status. The vent colors
                        will update in real time to reflect the active states
                        of the Zephyr vents.
                        
                        The "MONITORING" tab gives a more in-depth view to the
                        status of the vents. A specific vent can be selected
                        from the drop-down menu. Once a vent is selected, the
                        panel on the left side will display the vent's metadata
                        along with several quick stats. The interactive panel
                        on the right will display live plots of the temperature
                        and humidity readings taken from the selected vent.
                        
                        The "SETTINGS" tab allows you to select a specific vent
                        and then alter the some metadata of the vent as well as
                        the behaviour of the vent (e.g. when it should be open
                        and when it should be closed.
                        
                        ###### Source Code

                        This dashboard was built using Python 3 and the Plotly
                        Dash library. You can find the source code of this app
                        on our [Github repository](https://github.com/pzindel/capstone-project).


                                """
                            )
                        ),
                    ),
                ],
            )
        ),
    )


def build_tabs() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the tabs
    of the application which appears under the banner on the webpage.
    
    Returns:
        (dash.html.Div): A division element containing the tab sub-elements.
    """
    return html.Div(
        id="tabs",
        className="tabs",
        children=[
            dcc.Tabs(
                id="app-tabs",
                value="tab1",
                className="custom-tabs",
                children=[
                    dcc.Tab(
                        id="Floor-tab",
                        label="Floor Plan",
                        value="tab1",
                        className="custom-tab",
                        selected_className="custom-tab--selected",
                    ),
                    dcc.Tab(
                        id="Monitoring-tab",
                        label="Monitoring",
                        value="tab2",
                        className="custom-tab",
                        selected_className="custom-tab--selected",
                    ),
                    dcc.Tab(
                        id="Settings-tab",
                        label="Vent Settings",
                        value="tab3",
                        className="custom-tab",
                        selected_className="custom-tab--selected",
                    ),
                ],
            )
        ],
    )


# ===== General Tabs Section =====
@APP.callback(
    [Output("app-content", "children"), Output("interval-component", "n_intervals")],
    [Input("app-tabs", "value")],
    [State("n-interval-stage", "data")],
)
def render_tab_content(tab_switch: str, stopped_interval: int) -> (dash.html.Div, int):
    """
    A callback function that is triggered by selecting different tabs on the
    app webpage.
    
    Constructs the necessary HTML elements for the selected tab and sends the
    element to the container in the main app layout.
    
    Parameters:
        tab_switch (str): The identifier of which tab has been selected.
        stopped_interval (int): The number of program intervals.
    
    Returns:
        (dash.html.Div): A division element containing the tab sub-elements.
    """
    # Determine which tab has been selected
    if tab_switch == "tab1":
        return build_floorplan_tab(), stopped_interval
    elif tab_switch == "tab2":
        secondary_panel = build_chart_panel
        division_id = "graphs-container"
    else: #tab_switch == "tab3"
        secondary_panel = build_settings_panel
        division_id = "graphs-container"
    
    # Load the vent configuration data
    with open(CONFIG_FP, "r") as file:
        stats_summary = json.load(file)
    
    # Construct a list of vent devices for the drop-down menu
    dropdown_options = []
    for vent_addr in stats_summary.keys():
        vent_name = stats_summary.get(vent_addr).get("vent_description")
        dropdown_options.append({
            "label": f"{vent_name} - {vent_addr}",
            "value": vent_addr,
        })
    
    return (
        html.Div(
            children=[
                dcc.Dropdown(
                    options=dropdown_options,
                    id="demo-dropdown",
                    persistence=True,
                    persistence_type="session",
                ),
                html.Div(
                    id="status-container",
                    children=[
                        build_quick_stats_panel(),
                        html.Div(
                            id="graphs-container",
                            children=[secondary_panel()],
                        ),
                    ],
                ),
            ],
        ),
        stopped_interval,
    )


def build_quick_stats_panel() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the quick stats
    information panel found on the MONITORING and SETTINGS tabs of the
    application.
    
    Returns:
        (dash.html.Div): A division element containing the quick-stats sub-elements.
    """
    return html.Div(
        id="quick-stats",
        className="row",
        children=[
            html.Div(
                id="card-1",
                children=[],
            ),
        ],
    )


@APP.callback(
    output=Output("card-1", "children"),
    inputs=[
        Input("interval-component", "n_intervals"),
        Input("demo-dropdown", "value"),
    ],
)
def update_quick_stats(interval: int, value: str) -> list:
    """
    A callback function that is triggered by selecting different vents from the
    drop-down and at fixed time intervals.
    
    Constructs the necessary HTML elements for the quick statistics panel that
    gets displayed on certain tabs.
    
    Parameters:
        interval (int): The number of update intervals that have elapsed.
        value (str): The MAC address of the currenlty selected vent.
    
    Returns:
        (list): A list of HTML elements containing the quick stats info.
    """
    # Set stats defaults for when no vent has been selected
    vent_name = "-".upper()
    ble_name = "-".upper()
    ble_address = "-".upper()
    vent_state = "-".upper()
    signal_state = 0
    battery_state = 0
    
    # Check if a vent has been selected
    if value is not None:
        # Open the config of the selected vent
        with open(CONFIG_FP, "r") as file:
            vent_config = json.load(file)[value]
        
        # Map the config data to our variables
        ble_address = value.upper()
        ble_name = vent_config["device_name"].upper()
        vent_name = vent_config["vent_description"].upper()
        vent_state = "CLOSED" if vent_config["vent_closed"] else "OPEN"
        battery_state = vent_config["last_battery_level"] / 10
        # Note: the RSSI value needs to be scaled to a percentage
        # Anything over -50 is 100% and anything under -100 is 0%
        rssi_signal = vent_config["last_read_rssi"]
        signal_state = max(min((2 * (rssi_signal + 100)), 100), 0) / 10

    # Construct and return the panel
    return [
        html.P("Vent Name:"),
        html.P(vent_name,className="quick-stat-data"),
        html.P("BLE Name:"),
        html.P(ble_name, className="quick-stat-data"),
        html.P("BLE Address:"),
        html.P(ble_address, className="quick-stat-data"),
        html.P("Vent State:"),
        html.P(vent_state, className="quick-stat-data"),
        html.P("Signal Strength:"),
        html.Div(
            id="quick-stat-graduatedbar",
            children=daq.GraduatedBar(
                color={
                    "ranges": {
                        "#f45060": [0, 1],
                        "#f4d44d ": [1, 4],
                        "#92e0d3": [4, 10],
                    }
                },
                showCurrentValue=True,
                max=10,
                value=signal_state,
            ),
        ),
        html.P("Battery Level:"),
        html.Div(
            id="quick-stat-graduatedbar",
            children=daq.GraduatedBar(
                color={
                    "ranges": {
                        "#f45060": [0, 1],
                        "#f4d44d ": [1, 4],
                        "#92e0d3": [4, 10],
                    }
                },
                showCurrentValue=True,
                max=10,
                value=battery_state,
            ),
        ),
    ]


# Update interval
@APP.callback(
    Output("n-interval-stage", "data"),
    [Input("app-tabs", "value")],
    [
        State("interval-component", "n_intervals"),
        State("interval-component", "disabled"),
        State("n-interval-stage", "data"),
    ],
)
def update_interval_state(tab_switch: str, cur_interval: int, disabled: bool, cur_stage: int) -> int:
    """
    A callback function that is triggered by selecting different tabs on the
    app webpage.
    
    Returns the interval count or total count based on which tab is currently
    selected and if the interval counter is enabled.
    
    Parameters:
        tab_switch (str): The identifier of which tab has been selected.
        cur_interval (int): The number of intervals elapsed.
        disabled (bool): If the interval counter is disabled or not.
        cur_stage (int): The total count of intervals + the starting value.
    
    Returns:
        (int): The number of interval or total count.
    """
    if disabled or tab_switch == "tab1":
        return cur_interval
    else:
        return cur_stage


# ===== FLOOR-PLAN Tab Section =====
def build_floorplan_tab() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the elements for
    the Floor Plan tab of the application.
    
    Returns:
        (dash.html.Div): A division element containing the tab sub-elements.
    """
    return html.Div(
        id="floor-plan-container",
        children=[
            # The live floor plan with several overlapping transparent PNGs
            html.Div(
                id="floor-plan-image-container",
                children=[
                    html.Img(id="floor-img", src=APP.get_asset_url("img/floorplan_inverted.png")),
                    # These mask elements could allow for per room color gradients
                    # based on the temperatures present in the room.
                    #html.Img(id="mask-bedroom-1-img", src=APP.get_asset_url("img/mask_bedroom_1.png"), className="floor-mask-offline"),
                    #html.Img(id="mask-bedroom-2-img", src=APP.get_asset_url("img/mask_bedroom_2.png"), className="floor-mask-offline"),
                    #html.Img(id="mask-bathroom-img", src=APP.get_asset_url("img/mask_bathroom.png"), className="floor-mask-offline"),
                    #html.Img(id="mask-kitchen-img", src=APP.get_asset_url("img/mask_kitchen.png"), className="floor-mask-offline"),
                    #html.Img(id="mask-laundry-img", src=APP.get_asset_url("img/mask_laundry.png"), className="floor-mask-offline"),
                    #html.Img(id="mask-livingroom-img", src=APP.get_asset_url("img/mask_livingroom.png"), className="floor-mask-offline"),
                    html.Img(id="vent-bedroom-1-img", src=APP.get_asset_url("img/vent_bedroom_1.png"), className="vent-offline"),
                    html.Img(id="vent-bedroom-2-img", src=APP.get_asset_url("img/vent_bedroom_2.png"), className="vent-offline"),
                    html.Img(id="vent-bathroom-img", src=APP.get_asset_url("img/vent_bathroom.png"), className="vent-offline"),
                    html.Img(id="vent-kitchen-img", src=APP.get_asset_url("img/vent_kitchen.png"), className="vent-offline"),
                    html.Img(id="vent-laundry-img", src=APP.get_asset_url("img/vent_laundry.png"), className="vent-offline"),
                    html.Img(id="vent-livingroom-1-img", src=APP.get_asset_url("img/vent_livingroom_1.png"), className="vent-offline"),
                    html.Img(id="vent-livingroom-2-img", src=APP.get_asset_url("img/vent_livingroom_2.png"), className="vent-offline"),                        
                    # An interval element used to force callbacks at fixed intervals
                    dcc.Interval(
                        id="vent-update-interval",
                        interval=1000,  # in milliseconds
                        n_intervals=0,  # start at batch 0
                        disabled=False,
                    ),
                ],
            ),
            # The legend for the live floor plan
            html.Div(
                id="floor-plan-legend-container",
                children=[
                    # Legend: open vent
                    html.Div(
                        className="legend-entry",
                        children=[
                            html.Img(
                                id="open-vent-legend",
                                src=APP.get_asset_url("img/vent.png"),
                                style={
                                    "position": "relative",
                                    "height": "10rem",
                                    "filter": "invert(40%) sepia(100%) saturate(3200%) hue-rotate(130deg) brightness(100%) contrast(100%)"
                                }
                            ),
                            html.Div(
                                children=html.H3("Vent open"),
                                style={"padding-left": "2rem"},
                            ),
                        ],
                    ),
                    # Legend: closed vent
                    html.Div(
                        className="legend-entry",
                        children=[
                            html.Img(
                                id="closed-vent-legend",
                                src=APP.get_asset_url("img/vent.png"),
                                style={
                                    "position": "relative",
                                    "height": "10rem",
                                    "filter": "invert(20%) sepia(100%) saturate(3200%) hue-rotate(00deg) brightness(80%) contrast(100%)"
                                }
                            ),
                            html.Div(
                                children=html.H3("Vent closed"),
                                style={"padding-left": "2rem"},
                            ),
                        ],
                    ),
                    # Legend: low-battery vent
                    html.Div(
                        className="legend-entry",
                        children=[
                            html.Img(
                                id="battery-low-vent-legend",
                                src=APP.get_asset_url("img/vent.png"),
                                style={
                                    "position": "relative",
                                    "height": "10rem",
                                    "filter": "invert(60%) sepia(100%) saturate(3200%) hue-rotate(10deg) brightness(100%) contrast(100%)"
                                }
                            ),
                            html.Div(
                                children=html.H3("Unit battery is low"),
                                style={"padding-left": "2rem"},
                            ),
                        ],
                    ),
                    # Legend: offline vent
                    html.Div(
                        className="legend-entry",
                        children=[
                            html.Img(
                                id="offline-vent-legend",
                                src=APP.get_asset_url("img/vent.png"),
                                style={
                                    "position": "relative",
                                    "height": "10rem",
                                    "filter": "invert(0%) sepia(100%) saturate(3200%) hue-rotate(130deg) brightness(100%) contrast(100%)"
                                }
                            ),
                            html.Div(
                                children=html.H3("Unit is offline"),
                                style={"padding-left": "2rem"},
                            ),
                        ],
                    ),
                ],
            ),
        ],
    )


@APP.callback(
    output=[
        Output("vent-bedroom-1-img", "className"),
        Output("vent-bedroom-2-img", "className"),
        Output("vent-bathroom-img", "className"),
        Output("vent-kitchen-img", "className"),
        Output("vent-laundry-img", "className"),
        Output("vent-livingroom-1-img", "className"),
        Output("vent-livingroom-2-img", "className"),
    ],
    inputs=Input("vent-update-interval", "n_intervals"),
)
def update_vent_state(n_intervals: int) -> list:
    """
    A callback function that is triggered by regular intervals set by the
    floorplan tab element.
    
    Loads the latest version of the Zephyr vent configuration data and updates
    the floor plan vent colors based on their states.
    
    Parameters:
        n_intervals (int): The number of trigger intervals that have elapsed.
    
    Returns:
        (list): A list of className which determine the vent states and colors.
    """
    # Load a config file that maps the Dash vent names to their MAC addresses
    with open(VENTMAP_FP, "r") as file:
        vent_map = json.load(file)
    
    # Load the config file with vent status information
    with open(CONFIG_FP, "r") as file:
        config_data = json.load(file)
    
    # Loop over each of the vents and construct a list of states
    app_vent_names = [
        "vent_bedroom_1",
        "vent_bedroom_2",
        "vent_bathroom",
        "vent_kitchen",
        "vent_laundry",
        "vent_livingroom_1", 
        "vent_livingroom_2"
    ]
    vent_states = []
    for vent_i in app_vent_names:
        if vent_i in vent_map and vent_map[vent_i] in config_data:
            # Load the basic vent data
            vent_closed = config_data[vent_map[vent_i]]["vent_closed"]
            battery_level = config_data[vent_map[vent_i]]["last_battery_level"]
    
            # Determine the display state of the vent
            if battery_level <= 15:
                vent_states.append("vent-battery-low")
            elif vent_closed == 1:
                vent_states.append("vent-closed")
            elif vent_closed == 0:
                vent_states.append("vent-open")
            else:
                vent_states.append("vent-offline")
        else:
            vent_states.append("vent-offline")

    # Set the new states to the display
    return vent_states


# ===== MONITORING Tabs Section =====
def build_chart_panel() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the elements for
    the Monitoring tab of the application.
    
    Returns:
        (dash.html.Div): A division element containing the tab sub-elements.
    """
    return html.Div(
        id="control-chart-container",
        className="twelve columns",
        children=[
            html.Div(className="section-banner", children="Live Sensor Readings"),
            html.Div(id="control-chart-div", children=[]),
        ],
    )


@APP.callback(
    output=Output("control-chart-live", "figure"),
    inputs=[
        Input("interval-component", "n_intervals"),
        Input("demo-dropdown", "value"),
    ],
    state=[State("control-chart-live", "figure")],
)
def update_control_chart_figure(interval: int, value: str, cur_fig: go.Figure) -> go.Figure:
    """
    A callback function that is triggered by regular intervals and by selecting
    a vent unit in the drop-down menu.
    
    Loads the latest version copy of the vent time-series data, filters it
    based on the selected vent unit, and calls a helper function to build the
    live data plot.
    
    Parameters:
        interval (int): The number of trigger intervals that have elapsed.
        value (str): The device address selected by the drop-down menu.
        cur_fig (go.Figure): A Plotly Graph Object of the current figure that
            needs to be updated.
    
    Returns:
        (go.Figure): A Plotly Graph Object containing the updated plot.
    """
    # Check for a valid vent selection
    if value is None:
        return cur_fig
    else:
        # Load the time-series data
        all_vent_data = pd.read_csv(DATA_FP)
        
        # Compute a human-readable local timestamp
        all_vent_data["local_time"] = \
            pd.to_datetime(all_vent_data["utc_time"], unit="s") \
            + pd.TimedeltaIndex(all_vent_data["utc_offset"], unit="h")
        
        # Select the subset of data for the chosen vent unit
        current_vent_data = all_vent_data[all_vent_data["device_address"] == value]
        
        # Check if there is existing data for the chosen vent
        #if current_vent_data.empty:
        #    return cur_fig
        
        # Generate the new figure
        return generate_graph(interval, current_vent_data, value)


def generate_graph(interval: int, data: pd.DataFrame, value: str) -> go.Figure:
    """
    Builds and returns a Plotly Figure element containing the temperature and
    humidity plot for the given vent.
    
    Parameters:
        interval (int): The number of trigger intervals that have elapsed.
        data (Pandas DataFrame): The data that needs to be plotted.
        value (str): The device address selected by the drop-down menu.
        
    Returns:
        (go.Figure): A Plotly Graph Object containing the updated plot.
    """
    # Initialize a dual-axis figure
    fig = make_subplots(specs=[[{"secondary_y": True}]])
    
    # Add the temperature data to the left axis
    fig.add_trace(
        go.Scatter(x=data["local_time"], y=data["temperature"], name="Temperature", line=dict(color="#EF553B")),
        secondary_y=False,
    )
    
    # Add the humidity data to the right axis
    fig.add_trace(
        go.Scatter(x=data["local_time"], y=data["humidity"], name="Humidity", line=dict(color="#F4D44D")),
        secondary_y=True,
    )
    
    # Load the vent's config data for plotting threshold lines
    with open(CONFIG_FP, "r") as file:
        vent_config = json.load(file)[value]
    
    # Define a set of y-values for indicator lines
    upper_threshold = vent_config["temp_upper_threshold"]
    lower_threshold = vent_config["temp_lower_threshold"]
    room_temperature = 22
    room_humidity = 50
    ave_temp = data["temperature"].mean()
    ave_hum = data["humidity"].mean()
    
    # Define a set of x-values for plotting the horizontal indicator lines
    x_f = data["local_time"].max()
    x_i = data["local_time"].min()
    
    # Compute the data ranges for scaling label placements
    temp_range = max(data["temperature"].max(), room_temperature) - min(data["temperature"].min(), room_temperature)
    hum_range = max(data["humidity"].max(), room_humidity) - min(data["humidity"].min(), room_humidity)
    
    # Check if the dataframe is empty and update NaN values if so
    if data.empty:
        ave_temp = 0
        ave_hum = 0
        x_f = 1
        x_i = 0
        temp_range = room_temperature
        hum_range = room_humidity
    
    # Update the figure with new styling and indicator lines (with labels)
    fig.update_layout(dict(
        autosize=True,
        margin=dict(t=40),
        hovermode="closest",
        paper_bgcolor="rgba(0,0,0,0)",
        plot_bgcolor="rgba(0,0,0,0)",
        legend=dict(font=dict(color="darkgray"), orientation="h", x=0, y=1.1),
        font=dict(color="darkgray"),
        showlegend=True,
        xaxis=dict(
            zeroline=False,
            showgrid=False,
            title="Date & Time",
            showline=False,
            titlefont=dict(color="darkgray"),
        ),
        yaxis=dict(
            title="Temperature (°C)",
            showgrid=False,
            showline=False,
            zeroline=False,
            autorange=True,
            titlefont=dict(color="darkgray"),
        ),
        annotations=[
            {
                "x": 0.9,
                "y": ave_temp+0.03*temp_range,
                "xref": "paper",
                "yref": "y",
                "text": f"Average Temperature: {str(round(ave_temp, 2))}°C",
                "showarrow": False,
                "font": {"color": "#EF553B"},
            },
            {
                "x": 0.9,
                "y": ave_hum+0.03*hum_range,
                "xref": "paper",
                "yref": "y2",
                "text": f"Average Humidity: {str(round(ave_hum))}%",
                "showarrow": False,
                "font": {"color": "#F4D44D"},
            },
            {
                "x": 0.05,
                "y": room_temperature-0.03*temp_range,
                "xref": "paper",
                "yref": "y",
                "text": f"Room Temperature: {str(round(room_temperature, 2))}°C",
                "showarrow": False,
                "font": {"color": "#91dfd2"},
            },
            {
                "x": 0.05,
                "y": room_humidity-0.03*hum_range,
                "xref": "paper",
                "yref": "y2",
                "text": f"Room Humidity: {str(round(room_humidity))}%",
                "showarrow": False,
                "font": {"color": "#91dfd2"},
            },
            # These threshold indicators have been disabled for the demo.
            # {
                # "x": 0.05,
                # "y": 40+1,#upper_threshold,
                # "xref": "paper",
                # "yref": "y",
                # "text": f"Upper Temp Threshold: {str(round(upper_threshold, 2))}°C",
                # "showarrow": False,
                # "font": {"color": "white"},
            # },
            # {
                # "x": 0.05,
                # "y": 25+1,#lower_threshold,
                # "xref": "paper",
                # "yref": "y",
                # "text": f"Lower Temp Threshold: {str(round(lower_threshold, 2))}°C",
                # "showarrow": False,
                # "font": {"color": "white"},
            # },
        ],
        shapes=[
            {
                "type": "line",
                "xref": "x",
                "yref": "y",
                "x0": x_i,
                "y0": ave_temp,
                "x1": x_f,
                "y1": ave_temp,
                "line": {"color": "#EF553B", "width": 1, "dash": "dot"},
            },
            {
                "type": "line",
                "xref": "x",
                "yref": "y2",
                "x0": x_i,
                "y0": ave_hum,
                "x1": x_f,
                "y1": ave_hum,
                "line": {"color": "#F4D44D", "width": 1, "dash": "dot"},
            },
            {
                "type": "line",
                "xref": "x",
                "yref": "y",
                "x0": x_i,
                "y0": room_temperature,
                "x1": x_f,
                "y1": room_temperature,
                "line": {"color": "#91dfd2", "width": 2, "dash": "dot"},
            },
            {
                "type": "line",
                "xref": "x",
                "yref": "y2",
                "x0": x_i,
                "y0": room_humidity,
                "x1": x_f,
                "y1": room_humidity,
                "line": {"color": "#91dfd2", "width": 2, "dash": "dot"},
            },
            # These threshold indicators have been disabled for the demo.
            # {
                # "type": "line",
                # "xref": "x",
                # "yref": "y",
                # "x0": x_i,
                # "y0": 40,#upper_threshold,
                # "x1": x_f,
                # "y1": 40,#upper_threshold,
                # "line": {"color": "white", "width": 1},
            # },
            # {
                # "type": "line",
                # "xref": "x",
                # "yref": "y",
                # "x0": x_i,
                # "y0": 25,#lower_threshold,
                # "x1": x_f,
                # "y1": 25,#lower_threshold,
                # "line": {"color": "white", "width": 1},
            # },
        ],
        yaxis2=dict(
            title="Relative Humidity (%)",
            showgrid=False,
            showline=False,
            zeroline=False,
            autorange=True,
            titlefont=dict(color="darkgray"),
        ),
    ))

    return fig


@APP.callback(
    output=Output("control-chart-div", "children"),
    inputs=[
        Input("interval-component", "n_intervals"),
        Input("demo-dropdown", "value"),
    ],
)
def update_control_chart(interval: int, value: str):
    """
    A callback function that is triggered by regular intervals and by selecting
    a vent unit in the drop-down menu.
    
    Loads the latest version copy of the vent time-series data, filters it
    based on the selected vent unit, and calls a helper function to build the
    live data plot.
    
    Parameters:
        interval (int): The number of trigger intervals that have elapsed.
        value (str): The device address selected by the drop-down menu.
    
    Returns:
        (dash.html.Div or dcc.Graph):
            An HTML element containing placeholder text or a Dash Graph container.
    """
    # Check if a vent unit has been selected from the drop-down menu
    if value is None:
        # Provide placeholder text
        return html.Div(
            children=[html.Em("Select a device from the drop-down.")],
            style={"display": "flex", "flex-direction": "column", "align-items": "center", "padding": "5rem", "font-size": "1.5em"},
        )

    # Construct a Graph object to hold the live plots
    x = dcc.Graph(
        id="control-chart-live",
        figure=go.Figure(
            {
                "data": [
                    {
                        "x": [],
                        "y": [],
                        "mode": "lines+markers",
                        "name": "Temperature",
                    }
                ],
                "layout": {
                    "paper_bgcolor": "rgba(0,0,0,0)",
                    "plot_bgcolor": "rgba(0,0,0,0)",
                    "xaxis": dict(
                        showline=False, showgrid=False, zeroline=False
                    ),
                    "yaxis": dict(
                        showgrid=False, showline=False, zeroline=False
                    ),
                    "autosize": True,
                },
            }
        ),
    )

    return x


# ===== SETTINGS Tabs Section =====
def build_settings_panel() -> dash.html.Div:
    """
    Builds and returns a Dash HTML division element containing the elements for
    the Settings tab of the application.
    
    Returns:
        (dash.html.Div): A division element containing the tab sub-elements.
    """
    return html.Div(
        id="settings-subcontainer",
        className="twelve columns",
        children=[
            html.Div(className="section-banner", children="Settings"),
            html.Div(id="settings-div", children=[]),
        ],
    )


@APP.callback(
    output=Output("settings-div", "children"),
    inputs=[
        Input("demo-dropdown", "value"),
    ],
)
def update_settings_panel(value) -> dash.html.Div:
    """
    A callback function that is triggered by the selection of a vent unit in
    the drop-down menu.
    
    Loads the latest version of the vent's configuration data in a format
    that supports user changes to the configuration.
    
    Parameters:
        value (str): The device address selected by the drop-down menu.
    
    Returns:
        (dash.html.Div or dcc.Graph):
            An HTML element containing placeholder text or a Dash Graph container.
    """
    # Check if a device has been selected
    if value is None:
        # Provide placeholder text
        return html.Div(
            children=[html.Em("Select a device from the drop-down.")],
            style={"display": "flex", "flex-direction": "column", "align-items": "center", "padding": "5rem", "font-size": "1.5em"},
        )

    # Load the latest configuration data
    with open(CONFIG_FP, "r") as file:
        vent_config = json.load(file)[value]
    
    # Construct and return the form
    return html.Div(
        children=[
            html.Label("Vent Name:"),
            dcc.Input(
                id="vent-name-edit",
                type="text",
                value=vent_config["vent_description"]
            ),
            html.Label("Vent State:"),
            html.Div(
                children=[
                    daq.BooleanSwitch(
                        id="vent-state-edit",
                        on=bool(vent_config["vent_closed"]),
                        color="red",
                    ),
                ],
                style={"display": "flex"},
            ),
            html.Label("Upper Temperature Threshold:"),
            dcc.Input(
                id="upper-temp-threshold-edit",
                type="number",
                step=0.1,
                value=vent_config["temp_upper_threshold"]
            ),
            html.Label("Lower Temperature Threshold:"),
            dcc.Input(
                id="lower-temp-threshold-edit",
                type="number",
                step=0.1,
                value=vent_config["temp_lower_threshold"]),
            html.Label("Schedule:"),
            html.Em("COMING SOON"),
            html.Div(
                children=[
                    html.Button(
                        id="reset-settings-button",
                        children="Reset",
                        n_clicks=0,
                        style={"background-color": "lightgray"},
                    ),
                    html.Button(
                        id="save-settings-button",
                        children="Save",
                        n_clicks=0,
                        style={"background-color": "lightgray", "color": "black"},
                    ),
                ],
                style={"margin": "2rem 0rem 2rem 0rem"},
            ),
        ],
        style=dict(
            padding="2rem 4rem 2rem 4rem",
            margin="auto",
        ),
    )
    

@APP.callback(
    output=[
        Output("vent-name-edit", "value"),
        Output("vent-state-edit", "on"),
        Output("upper-temp-threshold-edit", "value"),
        Output("lower-temp-threshold-edit", "value"),
    ],
    inputs=[
        Input("reset-settings-button", "n_clicks"),
        Input("save-settings-button", "n_clicks"),
    ],
    state=[
        State("demo-dropdown", "value"),
        State("vent-name-edit", "value"),
        State("vent-state-edit", "on"),
        State("upper-temp-threshold-edit", "value"),
        State("lower-temp-threshold-edit", "value"),
    ],
)
def update_config_file(
    reset_click,
    save_click,
    device_address,
    new_vent_name,
    new_vent_state,
    new_upper_threshold,
    new_lower_threshold
) -> (str, bool, int, int):
    """
    A callback function that is triggered by the user pressing the 'RESET' or
    'SAVE' buttons on the Settings tab.
    
    If the 'RESET' button is pressed, the function loads the latest config data
    back into the settings form.
    If the 'SAVE' button is pressed, the function save the current state of the
    settings form to the configuration file for the selected vent.
    
    Parameters:
        reset_click (int): The device address selected by the drop-down menu.
        save_click (int): The device address selected by the drop-down menu.
        device_address (str): The device address selected by the drop-down menu.
        new_vent_name (str): The device address selected by the drop-down menu.
        new_vent_state (str): The device address selected by the drop-down menu.
        new_upper_threshold (int): The device address selected by the drop-down menu.
        new_lower_threshold (int): The device address selected by the drop-down menu.
    
    Returns:
        (str, bool, int, int):
            A tuple containing the new values of the settings form elements.
    """
    ctx = dash.callback_context
    
    # Load the currently saved configuration data
    with open(CONFIG_FP, "r") as file:
            config_data = json.load(file)

    # Check the cause of the callback function being called
    if ctx.triggered_id == "reset-settings-button":
        # Reset: use the saved config data to update/reset the values in the form
        new_vent_name = config_data[device_address]["vent_description"]
        new_vent_state = bool(config_data[device_address]["vent_closed"])
        new_upper_threshold = config_data[device_address]["temp_upper_threshold"]
        new_lower_threshold = config_data[device_address]["temp_lower_threshold"]

    elif ctx.triggered_id == "save-settings-button":
        # Save: overwrite the old config data with the new values
        config_data[device_address]["vent_description"] = new_vent_name
        config_data[device_address]["vent_closed"] = int(new_vent_state)
        config_data[device_address]["temp_upper_threshold"] = new_upper_threshold
        config_data[device_address]["temp_lower_threshold"] = new_lower_threshold
        
        # Save the new config dictionary to the file
        with open(CONFIG_FP, "w") as file:
            json.dump(config_data, file, indent=4)

    # Return the values of the elements
    return new_vent_name, new_vent_state, new_upper_threshold, new_lower_threshold
    


# MAIN FUNCTION

# Set up the main layout of the application
APP.layout = html.Div(
    id="big-app-container",
    children=[
        build_banner(),
        dcc.Interval(
            id="interval-component",
            interval=10 * 1000,  # in milliseconds
            n_intervals=50,  # start at batch 50
            disabled=False,
        ),
        html.Div(
            id="app-container",
            children=[
                build_tabs(),
                html.Div(id="app-content"), # Main app
            ],
        ),
        dcc.Store(id="n-interval-stage", data=50),
        generate_modal(),
    ],
)

if __name__ == "__main__":
    APP.run_server(debug=True, port=APP_PORT, host=APP_ADDRESS)
