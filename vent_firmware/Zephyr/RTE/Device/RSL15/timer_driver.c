/**
 * @file timer_driver.c
 * @brief Timer Driver implementation
 *
 * @copyright @parblock
 * Copyright (c) 2021 Semiconductor Components Industries, LLC (d/b/a
 * onsemi), All Rights Reserved
 *
 * This code is the property of onsemi and may not be redistributed
 * in any form without prior written permission from onsemi.
 * The terms of use and warranty for this code are covered by contractual
 * agreements between onsemi and the licensee.
 *
 * This is Reusable Code.
 * @endparblock
 */

#include <timer_driver.h>

#if RTE_TIMER

/* Driver Version Macro */
#define ARM_TIMER_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(0, 1)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_TIMER_API_VERSION,
    ARM_TIMER_DRV_VERSION
};

#if (RTE_TIMER0_EN)

/* Set default Timer0 configuration */
static const TIMER_CFG_t timer0_DefaultCfg = {                                  /* Timer 0 default configuration */
    .timer_cfg.mode          = (TIMER_MODE_t)(RTE_TIMER0_MODE_DEFAULT),         /* Timer 0 default mode */
    .timer_cfg.clk_src       = (TIMER_CLKSRC_t)(RTE_TIMER0_CLKSRC_DEFAULT),     /* Timer 0 default clock source */
    .timer_cfg.prescale_val  = (TIMER_PRESCALE_t)(RTE_TIMER0_PRESCALE_DEFAULT), /* Timer 0 default prescale value */
    .timer_cfg.multi_cnt     = 
        (TIMER_MULTI_COUNT_t)(RTE_TIMER0_MULTI_COUNT_DEFAULT),                  /* Timer 0 default multi count value */
    .timer_cfg.timeout_val   = RTE_TIMER0_TIMEOUT_DEFAULT,                      /* Timer 0 default timeout value */
#if (RTE_GPIO0_EN)
    .timer_cfg.gpio_mode     =
        (TIMER_GPIO_INT_MODE_t)(RTE_TIMER0_GPIO_MODE_DEFAULT),                  /* Timer 0 GPIO default mode */
    .timer_cfg.gpio_int      = (TIMER_GPIO_t)(RTE_TIMER0_GPIO_INT_DEFAULT)      /* Timer 0 default GPIO value */
#endif /* if (RTE_GPIO_EN) */
};
static const TIMER_PRI_CFG_t timer0_DefaultPri = {                            /* Timer 0 default interrupt priority configuration */
    .preempt_pri             = RTE_TIMER0_INT_PREEMPT_PRI,                    /* Timer 0 default pre-empt priority value */
    .subgrp_pri              = RTE_TIMER0_INT_SUBGRP_PRI                      /* Timer 0 default subgroup priority value */
};
#endif /* if (RTE_TIMER0_EN) */

#if (RTE_TIMER1_EN)

/* Set default Timer1 configuration */
static const TIMER_CFG_t timer1_DefaultCfg = {                                  /* Timer 1 default configuration */
    .timer_cfg.mode          = (TIMER_MODE_t)(RTE_TIMER1_MODE_DEFAULT),         /* Timer 1 default mode */
    .timer_cfg.clk_src       = (TIMER_CLKSRC_t)(RTE_TIMER1_CLKSRC_DEFAULT),     /* Timer 1 default clock source */
    .timer_cfg.prescale_val  = (TIMER_PRESCALE_t)(RTE_TIMER1_PRESCALE_DEFAULT), /* Timer 1 default prescale value */
    .timer_cfg.multi_cnt     = 
        (TIMER_MULTI_COUNT_t)(RTE_TIMER1_MULTI_COUNT_DEFAULT),                  /* Timer 1 default multi count value */
    .timer_cfg.timeout_val   = RTE_TIMER1_TIMEOUT_DEFAULT,                      /* Timer 1 default timeout value */
#if (RTE_GPIO1_EN)
    .timer_cfg.gpio_mode     =
        (TIMER_GPIO_INT_MODE_t)(RTE_TIMER1_GPIO_MODE_DEFAULT),                  /* Timer 1 GPIO default mode */
    .timer_cfg.gpio_int      = (TIMER_GPIO_t)(RTE_TIMER1_GPIO_INT_DEFAULT)      /* Timer 1 default GPIO value */
#endif /* if (RTE_GPIO_EN) */
};
static const TIMER_PRI_CFG_t timer1_DefaultPri = {                            /* Timer 1 default interrupt priority configuration */
    .preempt_pri             = RTE_TIMER1_INT_PREEMPT_PRI,                    /* Timer 1 default pre-empt priority value */
    .subgrp_pri              = RTE_TIMER1_INT_SUBGRP_PRI                      /* Timer 1 default subgroup priority value */
};
#endif /* if (RTE_TIMER1_EN) */

#if (RTE_TIMER2_EN)

/* Set default Timer2 configuration */
static const TIMER_CFG_t timer2_DefaultCfg = {                                /* Timer 2 default configuration */
    .timer_cfg.mode          = (TIMER_MODE_t)RTE_TIMER2_MODE_DEFAULT,         /* Timer 2 default mode */
    .timer_cfg.clk_src       = (TIMER_CLKSRC_t)RTE_TIMER2_CLKSRC_DEFAULT,     /* Timer 2 default clock source */
    .timer_cfg.prescale_val  = (TIMER_PRESCALE_t)RTE_TIMER2_PRESCALE_DEFAULT, /* Timer 2 default prescale value */
    .timer_cfg.multi_cnt     = 
        (TIMER_MULTI_COUNT_t)RTE_TIMER2_MULTI_COUNT_DEFAULT,                  /* Timer 2 default multi count value */
    .timer_cfg.timeout_val   = RTE_TIMER2_TIMEOUT_DEFAULT,                    /* Timer 2 default timeout value */
#if (RTE_GPIO2_EN)
    .timer_cfg.gpio_mode     =
        (TIMER_GPIO_INT_MODE_t)RTE_TIMER2_GPIO_MODE_DEFAULT,                  /* Timer 2 GPIO default mode */
    .timer_cfg.gpio_int      = (TIMER_GPIO_t)RTE_TIMER2_GPIO_INT_DEFAULT      /* Timer 2 default GPIO value */
#endif /* if (RTE_GPIO_EN) */
};
static const TIMER_PRI_CFG_t timer2_DefaultPri = {                            /* Timer 2 default interrupt priority configuration */
    .preempt_pri             = RTE_TIMER2_INT_PREEMPT_PRI,                    /* Timer 2 default pre-empt priority value */
    .subgrp_pri              = RTE_TIMER2_INT_SUBGRP_PRI                      /* Timer 2 default subgroup priority value */
};
#endif /* if (RTE_TIMER2_EN) */

#if (RTE_TIMER3_EN)

/* Set default Timer3 configuration */
static const TIMER_CFG_t timer3_DefaultCfg = {                                /* Timer 3 default configuration */
    .timer_cfg.mode          = (TIMER_MODE_t)RTE_TIMER3_MODE_DEFAULT,         /* Timer 3 default mode */
    .timer_cfg.clk_src       = (TIMER_CLKSRC_t)RTE_TIMER3_CLKSRC_DEFAULT,     /* Timer 3 default clock source */
    .timer_cfg.prescale_val  = (TIMER_PRESCALE_t)RTE_TIMER3_PRESCALE_DEFAULT, /* Timer 3 default prescale value */
    .timer_cfg.multi_cnt     = 
        (TIMER_MULTI_COUNT_t)RTE_TIMER3_MULTI_COUNT_DEFAULT,                  /* Timer 3 default multi count value */
    .timer_cfg.timeout_val   = RTE_TIMER3_TIMEOUT_DEFAULT,                    /* Timer 3 default timeout value */
#if (RTE_GPIO3_EN)
    .timer_cfg.gpio_mode     =
        (TIMER_GPIO_INT_MODE_t)RTE_TIMER3_GPIO_MODE_DEFAULT,                  /* Timer 3 GPIO default mode */
    .timer_cfg.gpio_int      = (TIMER_GPIO_t)RTE_TIMER3_GPIO_INT_DEFAULT      /* Timer 3 default GPIO value */
#endif /* if (RTE_GPIO_EN) */
};
static const TIMER_PRI_CFG_t timer3_DefaultPri = {                            /* Timer 3 default interrupt priority configuration */
    .preempt_pri             = RTE_TIMER3_INT_PREEMPT_PRI,                    /* Timer 3 default pre-empt priority value */
    .subgrp_pri              = RTE_TIMER3_INT_SUBGRP_PRI                      /* Timer 3 default subgroup priority value */
};
#endif /* if (RTE_TIMER3_EN) */

#if (RTE_SYSTICK_EN)

/* Set default SysTick configuration */
static const TIMER_CFG_t systick_DefaultCfg = {                 /* SysTick default configuration */
    .systick_cfg.clk_src          = RTE_SYSTICK_CLKSRC_DEFAULT, /* SysTick default clock source */
    .systick_cfg.reload_val       = RTE_SYSTICK_RELOAD_DEFAULT, /* SysTick default reload value */
};
static const TIMER_PRI_CFG_t systick_DefaultPri = {             /* SysTick default interrupt priorities */
    .preempt_pri             = RTE_SYSTICK_INT_PREEMPT_PRI,     /* SysTick default pre-empt priority value */
    .subgrp_pri              = RTE_SYSTICK_INT_SUBGRP_PRI       /* SysTick default subgroup priority value */
};
#endif /* if (RTE_SYSTICK_EN) */

/* Timer run-time information */
static TIMER_INFO_t TIMER_Info = {
    .flags = 0,                                                 /* Timer flags */
#if (RTE_TIMER0_EN)
    .default_cfg[0]     = &timer0_DefaultCfg,                   /* Timer0 default configuration */
    .default_pri_cfg[0] = &timer0_DefaultPri,                   /* Timer0 default interrupt priorities */
#endif /* if (RTE_TIMER0_EN) */
#if (RTE_TIMER1_EN)
    .default_cfg[1]     = &timer1_DefaultCfg,                   /* Timer1 default configuration */
    .default_pri_cfg[1] = &timer1_DefaultPri,                   /* Timer1 default interrupt priorities */
#endif /* if (RTE_TIMER1_EN) */
#if (RTE_TIMER2_EN)
    .default_cfg[2]     = &timer2_DefaultCfg,                   /* Timer2 default configuration */
    .default_pri_cfg[2] = &timer2_DefaultPri,                   /* Timer2 default interrupt priorities */
#endif /* if (RTE_TIMER2_EN) */
#if (RTE_TIMER3_EN)
    .default_cfg[3]     = &timer3_DefaultCfg,                   /* Timer3 default configuration */
    .default_pri_cfg[3] = &timer3_DefaultPri,                   /* Timer3 default interrupt priorities */
#endif /* if (RTE_TIMER3_EN) */
#if (RTE_SYSTICK_EN)
    .default_cfg[4]     = &systick_DefaultCfg,                  /* SysTick default configuration */
    .default_pri_cfg[4] = &systick_DefaultPri,                  /* Timer4 default interrupt priorities */
#endif /* if (RTE_SYSTICK_EN) */
};

/* Timer resources */
static TIMER_RESOURCES_t TIMER_Resources =
{
    .info = &TIMER_Info,                                        /* Timer run-time information */
    .intInfo = {                                                /* Timer interrupt info */
        .irqn[TIMER_0]       = TIMER0_IRQn,                     /* Timer0 interrupt number */
        .irqn[TIMER_1]       = TIMER1_IRQn,                     /* Timer1 interrupt number */
        .irqn[TIMER_2]       = TIMER2_IRQn,                     /* Timer2 interrupt number */
        .irqn[TIMER_3]       = TIMER3_IRQn,                     /* Timer3 interrupt number */
        .irqn[TIMER_SYSTICK] = SysTick_IRQn,                    /* SysTick interrupt number */
        .cb = 0                                                 /* Timer interrupt handler */
    }
};

/**
 * @brief       Get driver version
 * @return      ARM_DRIVER_VERSION
 */
static ARM_DRIVER_VERSION TIMER_GetVersion (void)
{
    /* Return driver version */
    return DriverVersion;
}
/**
 * @brief       Get Timer Type
 * @param[in]   sel Timer to be configured
 * @return      TIMER_TYPE
 */
TIMER_Type * getTimer(TIMER_SEL_t sel){
	TIMER_Type * timer;
	switch(sel){
	case TIMER_0:
		timer = TIMER0;
		break;
	case TIMER_1:
		timer = TIMER1;
		break;
	case TIMER_2:
		timer = TIMER2;
		break;
	default:
        timer = TIMER3;
        break;
	}
	return timer;
}

/**
 * @brief       Initialize Timer
 * @param[in]   sel Timer to be configured
 * @param[in]   cfg Timer configuration
 * @return      ARM Driver return code
 */
static int32_t TIMER_Configure (TIMER_SEL_t sel, const TIMER_CFG_t *cfg)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

#if (RTE_SYSTICK_EN)

    /* Configure SysTick if SysTick was selected */
    if (sel == TIMER_SYSTICK)
    {
        /* Set the clock source */
        SysTick->CTRL = cfg->systick_cfg.clk_src << SysTick_CTRL_CLKSOURCE_Pos;

        /* Set the reload value */
        SysTick->LOAD = cfg->systick_cfg.reload_val;
    }
#endif /* if (RTE_SYSTICK_EN) */

#if (TIMER_REG_EN_MSK)

    /* Configure Timer if Timer was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
    	/* Prepare Prescale Word */
    	uint32_t prescaleWord = (cfg->timer_cfg.prescale_val << TIMER_CFG0_PRESCALE_Pos);

        /* Prepare config Word */
        uint32_t cfgWord = (cfg->timer_cfg.multi_cnt    << TIMER_CFG1_MULTI_COUNT_Pos) |
                           (cfg->timer_cfg.mode         << TIMER_CFG1_MODE_Pos)        |
                           (cfg->timer_cfg.clk_src      << TIMER_CFG1_CLK_SRC_Pos)     |
						   (cfg->timer_cfg.gpio_mode    << TIMER_CFG1_GPIO_INT_MODE_Pos) |
						   (cfg->timer_cfg.gpio_int     << TIMER_CFG1_GPIO_INT_SRC_Pos);

        /* Set the timeout */
        uint32_t timeout = (cfg->timer_cfg.timeout_val  << TIMER_CFG0_TIMEOUT_VALUE_Pos);

        /* Set the configuration word */
        Sys_Timer_Config(timer, prescaleWord, cfgWord, timeout);
    }
#endif /* if (TIMER_REG_EN_MSK) */

    /* Indicate that TIMERx was Initialized */
    TIMER_Resources.info->flags |= TIMER_FLAG_BIT_SET << sel;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Configure Timer interrupt priority.
 * @param[in]   sel Timer to be configured
 * @param[in]   cfg Interrupt priority configuration
 * @return      ARM_DRIVER_OK
 */
static int32_t TIMER_SetInterruptPriority(TIMER_SEL_t sel, const TIMER_PRI_CFG_t *cfg)
{
    /* Encoded priority value */
    uint32_t encodedPri = 0;

    /* Encode priority configuration word */
    encodedPri = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), cfg->preempt_pri, cfg->subgrp_pri);

    /* Set the Timer priority */
    NVIC_SetPriority(TIMER_Resources.intInfo.irqn[sel], encodedPri);

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Initialize the Timer driver
 * @param[in]   cb Callback function to be called on Timer event
 * @return      ARM_DRIVER_OK
 */
static int32_t TIMER_Initialize(TIMER_SignalEvent_t cb)
{
    /* Configure each enabled Timer module */
    for (int i = 0; i < TIMER_TIMERS_NUMBER; ++i)
    {
        /* Check if particular Timer should be initialized */
        if ((TIMER_FLAG_BIT_SET << i) & TIMER_EN_MSK)
        {
            /* Configure particular Timer */
            TIMER_Configure((TIMER_SEL_t)i, TIMER_Resources.info->default_cfg[i]);

            /* Set the particuar Timer interrupts priority */
            TIMER_SetInterruptPriority((TIMER_SEL_t)i, TIMER_Resources.info->default_pri_cfg[i]);

            /* Indicate that Timer was Initialized */
            TIMER_Resources.info->flags |= TIMER_FLAG_BIT_SET << i;
        }
    }

    /* Set the callback function */
    TIMER_Resources.intInfo.cb = cb;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start the particular Timer
 * @param[in]   sel Number of the Timer to be read.
 * @return      Execution status
 */
static int32_t TIMER_Start(TIMER_SEL_t sel)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

#if (RTE_SYSTICK_EN)
    /* Check if SysTick was selected */
    if (sel == TIMER_SYSTICK)
    {
        /* Enable SysTick interrupt and SysTick Timer*/
        SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) | (1 << SysTick_CTRL_ENABLE_Pos);
    }
#endif /* if (RTE_SYSTICK_EN) */

#if (TIMER_REG_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
        /* Clear pending flag */
        NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[sel]);

        /* Enable the interrupt */
        NVIC_EnableIRQ(TIMER_Resources.intInfo.irqn[sel]);

        /* Start the Timer */
        Sys_Timer_Start(timer);
    }
#endif /* if (TIMER_REG_EN_MSK) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Stop the particular Timer
 * @param[in]   sel Number of the Timer to be read.
 * @return      Execution status
 */
static int32_t TIMER_Stop(TIMER_SEL_t sel)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

#if (RTE_SYSTICK_EN)
    /* Check if SysTick was selected */
    if (sel == TIMER_SYSTICK)
    {
        /* Disable the SysTick interrupt and disable the SysTick Timer */
        SysTick->CTRL &= ~((1 << SysTick_CTRL_TICKINT_Pos) | (1 << SysTick_CTRL_ENABLE_Pos));
    }
#endif /* if (RTE_SYSTICK_EN) */

#if (TIMER_REG_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
        /* Disable the interrupt */
        NVIC_DisableIRQ(TIMER_Resources.intInfo.irqn[sel]);

        /* Clear pending flag */
        NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[sel]);

        /* Stop the Timer */
        Sys_Timer_Stop(timer);
    }
#endif /* if (TIMER_REG_EN_MSK) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set value of the Timer / SysTick
 * @param[in]   sel Number of the Timer to be read.
 * @param[in]   val Timer / SysTick value
 * @return      Execution status
 */
static int32_t TIMER_SetValue(TIMER_SEL_t sel, uint32_t val)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

#if (RTE_SYSTICK_EN)
    /* Check if SysTick was selected */
    if (sel == TIMER_SYSTICK)
    {
        /* Set SysTick reload value */
        SysTick->VAL = val;
    }
#endif /* if (RTE_SYSTICK_EN) */

#if (TIMER_REG_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
        /* Set SysTick Timer value */
        timer->CFG0 &= ~TIMER_CFG0_TIMEOUT_VALUE_Mask;
        timer->CFG0 |= val << TIMER_CFG0_TIMEOUT_VALUE_Pos;
    }
#endif /* if (TIMER_REG_EN_MSK) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set GPIO interrupt capture status
 * @param[in]   sel Number of the Timer to be read.
 * @return      Execution status
 */
static int32_t TIMER_SetGPIOInterrupt(TIMER_SEL_t sel)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }


#if (TIMER_GPIO_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
    	timer->CFG1 |= TIMER_GPIO_INT_ENABLE;
    }
#endif /* if (TIMER_GPIO_EN_MSK) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Get value of the Timer
 * @param[in]   sel Number of the Timer to be read.
 * @return      Timer value
 */
static uint32_t TIMER_GetValue(TIMER_SEL_t sel)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return 0;
    }

#if (RTE_SYSTICK_EN)
    /* Check if SysTick was selected */
    if (sel == TIMER_SYSTICK)
    {
        /* Return current SysTick value */
        return SysTick->VAL;
    }
#endif /* if (RTE_SYSTICK_EN) */

#if (TIMER_REG_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
        /* Return the current Timer value */
        return timer->VAL;
    }
#endif /* if (TIMER_REG_EN_MSK) */

    /* To avoid no return warning - should never be here */
    return 0;
}

/**
 * @brief       Get value of the Timer
 * @param[in]   sel Number of the Timer to be read.
 * @return      Timer capture value
 */
static uint32_t TIMER_GetValueCapture(TIMER_SEL_t sel)
{
    /* Check if correct Timer was selected */
    if (!((TIMER_FLAG_BIT_SET << sel) & TIMER_EN_MSK))
    {
        return 0;
    }

#if (TIMER_GPIO_EN_MSK)
    /* Check if SysTick was selected */
    if (sel != TIMER_SYSTICK)
    {
    	TIMER_Type * timer = getTimer(sel);
        /* Return the current Timer value */
        return timer->VAL_CAPTURE;
    }
#endif /* if (TIMER_GPIO_EN_MSK) */

    /* To avoid no return warning - should never be here */
    return 0;
}

/**
 * @brief       Get the current SysTick value
 * @return      1 if SysTick has already reached 0, otherwise 0
 */
static uint32_t TIMER_GetSysTickState(void)
{
#if (RTE_SYSTICK_EN)

    /* Return 1 if SysTick has already reached 0 */
    return (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) >> SysTick_CTRL_COUNTFLAG_Pos;
#else  /* if (RTE_SYSTICK_EN) */

    /* Return 0 as Timer is not supported */
    return 0;
#endif /* if (RTE_SYSTICK_EN) */
}

#if (RTE_TIMER0_EN)
/**
 * @brief       Called by hardware ISR when a Timer event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void TIMER0_IRQHandler(void)
{
    /* Disable TIMER interrupt */
    NVIC_DisableIRQ(TIMER_Resources.intInfo.irqn[TIMER_0]);

    /* Check if callback was set */
    if (TIMER_Resources.intInfo.cb)
    {
        /* Execute application callback */
        TIMER_Resources.intInfo.cb(TIMER_TIMER0_EVENT);
    }

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[TIMER_0]);

    /* Enable the interrupt */
    NVIC_EnableIRQ(TIMER_Resources.intInfo.irqn[TIMER_0]);
}

#endif /* if (RTE_TIMER0_EN) */

#if (RTE_TIMER1_EN)
/**
 * @brief       Called by hardware ISR when a Timer event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void TIMER1_IRQHandler(void)
{
    /* Disable Timer interrupt */
    NVIC_DisableIRQ(TIMER_Resources.intInfo.irqn[TIMER_1]);

    /* Check if callback was set */
    if (TIMER_Resources.intInfo.cb)
    {
        /* Execute application callback */
        TIMER_Resources.intInfo.cb(TIMER_TIMER1_EVENT);
    }

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[TIMER_1]);

    /* Enable the interrupt */
    NVIC_EnableIRQ(TIMER_Resources.intInfo.irqn[TIMER_1]);
}

#endif /* if (RTE_TIMER1_EN) */

#if (RTE_TIMER2_EN)
/**
 * @brief       Called by hardware ISR when a Timer event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void TIMER2_IRQHandler(void)
{
    /* Disable Timer interrupt */
    NVIC_DisableIRQ(TIMER_Resources.intInfo.irqn[TIMER_2]);

    /* Check if callback was set */
    if (TIMER_Resources.intInfo.cb)
    {
        /* Execute application callback */
        TIMER_Resources.intInfo.cb(TIMER_TIMER2_EVENT);
    }

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[TIMER_2]);

    /* Enable the interrupt */
    NVIC_EnableIRQ(TIMER_Resources.intInfo.irqn[TIMER_2]);
}

#endif /* if (RTE_TIMER2_EN) */

#if (RTE_TIMER3_EN)
/**
 * @brief       Called by hardware ISR when a Timer event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void TIMER3_IRQHandler(void)
{
    /* Disable Timer interrupt */
    NVIC_DisableIRQ(TIMER_Resources.intInfo.irqn[TIMER_3]);

    /* Check if callback was set */
    if (TIMER_Resources.intInfo.cb)
    {
        /* Execute application callback */
        TIMER_Resources.intInfo.cb(TIMER_TIMER3_EVENT);
    }

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(TIMER_Resources.intInfo.irqn[TIMER_3]);

    /* Enable the interrupt */
    NVIC_EnableIRQ(TIMER_Resources.intInfo.irqn[TIMER_3]);
}

#endif /* if (RTE_TIMER3_EN) */

#if (RTE_SYSTICK_EN)
/**
 * @brief       Called by hardware ISR when a SysTick event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void SysTick_Handler(void)
{
    /* Check if callback was set */
    if (TIMER_Resources.intInfo.cb)
    {
        /* Execute application callback */
        TIMER_Resources.intInfo.cb(TIMER_SYSTICK_EVENT);
    }
}

#endif /* if (RTE_SYSTICK_EN) */

/* Timer Driver Control Block */
DRIVER_TIMER_t Driver_TIMER =
{
    TIMER_GetVersion,
    TIMER_Initialize,
    TIMER_Configure,
    TIMER_SetInterruptPriority,
    TIMER_Start,
    TIMER_Stop,
    TIMER_SetValue,
	TIMER_SetGPIOInterrupt,
    TIMER_GetValue,
	TIMER_GetValueCapture,
    TIMER_GetSysTickState
};

#endif    /* RTE_TIMER */
