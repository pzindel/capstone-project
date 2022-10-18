/**
 * @file pwm_driver.c
 * @brief PWM Driver implementation
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

#include <Driver_GPIO.h>
#include <pwm_driver.h>

#if RTE_PWM

/* Driver Version Macro */
#define ARM_PWM_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(0, 1)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_PWM_API_VERSION,
    ARM_PWM_DRV_VERSION
};

/* Set default PWM0 configuration */
#if (RTE_PWM0_EN)
static const PWM_DEFAULT_CFG_t pwm0_DefaultCfg = {
    .pwm_default_cfg = {                                  /* PWM 0 default configuration */
        .period              = RTE_PWM0_PER_DEFAULT,      /* PWM 0 default period */
        .high_cycle          = RTE_PWM0_DTC_DEFAULT,       /* PWM 0 default duty cycle */
        .dithering           = RTE_PWM0_DITH_DEFAULT     /* PWM 0 default dithering */
    },
    .pwm_default_GPIO_cfg = {                             /* PWM 0 default GPIO configuration */
        .GPIO_pin             = RTE_PWM0_GPIO_PIN         /* PWM 0 default GPIO pad number */
    }
};
#endif /* if (RTE_PWM0_EN) */

/* Set default PWM1 configuration */
#if (RTE_PWM1_EN)
static const PWM_DEFAULT_CFG_t pwm1_DefaultCfg = {
    .pwm_default_cfg = {                                  /* PWM 1 default configuration */
        .period              = RTE_PWM1_PER_DEFAULT,      /* PWM 1 default period */
        .high_cycle          = RTE_PWM1_DTC_DEFAULT,      /* PWM 1 default duty cycle */
        .dithering           = RTE_PWM1_DITH_DEFAULT,     /* PWM 1 default dithering */
        .offset              = RTE_PWM1_OFF_DEFAULT       /* PWM 1 default offset */
    },
    .pwm_default_GPIO_cfg = {                             /* PWM 1 default GPIO configuration */
        .GPIO_pin             = RTE_PWM1_GPIO_PIN         /* PWM 1 default GPIO pad number */
    }
};
#endif /* if (RTE_PWM1_EN) */

/* Set default PWM2 configuration */
#if (RTE_PWM2_EN)
static const PWM_DEFAULT_CFG_t pwm2_DefaultCfg = {
    .pwm_default_cfg = {                                  /* PWM 2 default configuration */
        .period              = RTE_PWM2_PER_DEFAULT,      /* PWM 2 default period */
        .high_cycle          = RTE_PWM2_DTC_DEFAULT,      /* PWM 2 default duty cycle */
        .dithering           = RTE_PWM2_DITH_DEFAULT,     /* PWM 2 default dithering */
        .offset              = RTE_PWM2_OFF_DEFAULT       /* PWM 2 default offset */
    },
    .pwm_default_GPIO_cfg = {                             /* PWM 2 default GPIO configuration */
        .GPIO_pin             = RTE_PWM2_GPIO_PIN         /* PWM 2 default GPIO pad number */
    }
};
#endif /* if (RTE_PWM2_EN) */

/* Set default PWM3 configuration */
#if (RTE_PWM3_EN)
static const PWM_DEFAULT_CFG_t pwm3_DefaultCfg = {
    .pwm_default_cfg = {                                  /* PWM 3 default configuration */
        .period              = RTE_PWM3_PER_DEFAULT,      /* PWM 3 default period */
        .high_cycle          = RTE_PWM3_DTC_DEFAULT,      /* PWM 3 default duty cycle */
        .dithering           = RTE_PWM3_DITH_DEFAULT,     /* PWM 3 default dithering */
        .offset              = RTE_PWM3_OFF_DEFAULT       /* PWM 3 default offset */
    },
    .pwm_default_GPIO_cfg = {                             /* PWM 3 default GPIO configuration */
        .GPIO_pin             = RTE_PWM3_GPIO_PIN         /* PWM 3 default GPIO pad number */
    }
};
#endif /* if (RTE_PWM3_EN) */

/* Set default PWM4 configuration */
#if (RTE_PWM4_EN)
static const PWM_DEFAULT_CFG_t pwm4_DefaultCfg = {
    .pwm_default_cfg = {                                  /* PWM 4 default configuration */
        .period              = RTE_PWM4_PER_DEFAULT,      /* PWM 4 default period */
        .high_cycle          = RTE_PWM4_DTC_DEFAULT,      /* PWM 4 default duty cycle */
        .dithering           = RTE_PWM4_DITH_DEFAULT,     /* PWM 4 default dithering */
        .offset              = RTE_PWM4_OFF_DEFAULT       /* PWM 4 default offset */
    },
    .pwm_default_GPIO_cfg = {                             /* PWM 4 default GPIO configuration */
        .GPIO_pin             = RTE_PWM4_GPIO_PIN         /* PWM 4 default GPIO pad number */
    }
};
#endif /* if (RTE_PWM4_EN) */

/* PWM run-time information */
static PWM_INFO_t PWM_Info = {
    .flags = 0,                                           /* PWM flags */

#if (RTE_PWM0_EN)
    .default_cfg[0]          = &pwm0_DefaultCfg,          /* PWM 0 default configuration */
#endif /* if (RTE_PWM0_EN) */

#if (RTE_PWM1_EN)
    .default_cfg[1]          = &pwm1_DefaultCfg,          /* PWM 1 default configuration */
#endif /* if (RTE_PWM1_EN) */

#if (RTE_PWM2_EN)
    .default_cfg[2]          = &pwm2_DefaultCfg,          /* PWM 2 default configuration */
#endif /* if (RTE_PWM2_EN) */

#if (RTE_PWM3_EN)
    .default_cfg[3]          = &pwm3_DefaultCfg,          /* PWM 3 default configuration */
#endif /* if (RTE_PWM3_EN) */

#if (RTE_PWM4_EN)
    .default_cfg[4]          = &pwm4_DefaultCfg,          /* PWM 4 default configuration */
#endif /* if (RTE_PWM4_EN) */

};

/* PWM resources */
static PWM_RESOURCES_t PWM_Resources =
{
    &PWM_Info,                                            /* PWM run-time information */
};

/**
 * @brief       Get driver version
 * @return      Execution status
 * @assumptions None
 */
static ARM_DRIVER_VERSION PWM_GetVersion (void)
{
    /* Return driver version */
    return DriverVersion;
}

/**
 * @brief       Select the clock for the PWM block
 * @param[in]   clock_src    		Clock source (0 = SYSCLK, 1 = SLOWCLK)
 * @param[in]   slowclk_prescale    Prescaler for SLOWCLK (0-63)
 * @return      Execution status
 * @assumptions PWM period has been already configured
 */
static int32_t PWM_SelectClock (uint8_t clock_src, uint8_t slowclk_prescale)
{
	/* Check if correct values were passed */
    if ((clock_src != 0)&(clock_src != 1))
	{
    	return ARM_DRIVER_ERROR_PARAMETER;
	}

    if (slowclk_prescale > 63)
	{
    	return ARM_DRIVER_ERROR_PARAMETER;
	}

	/* Select clock source for PWM */
	switch (clock_src){

		case 0:
			CLK->DIV_CFG2 = (CLK->DIV_CFG2 & ~(1<<CLK_DIV_CFG2_PWM_CLK_SRC_Pos)) | PWM_SRC_SYSCLK;
			break;

		case 1:
			CLK_DIV_CFG0->SLOWCLK_PRESCALE_BYTE = slowclk_prescale;
			CLK->DIV_CFG2 |= PWM_SRC_SLOWCLK;
			break;
	}

	/* Return OK */
	return ARM_DRIVER_OK;
}

/**
 * @brief       Reset the PWM channel
 * @param[in]   sel    PWM channel to be reset
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_Reset(PWM_SEL_t sel)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

	/* Reset PWM channel */
	switch (sel){

	case 0:
		PWM->CTRL |= PWM0_RESET;
		break;

	case 1:
		PWM->CTRL |= PWM1_RESET;
		break;

	case 2:
		PWM->CTRL |= PWM2_RESET;
		break;

	case 3:
		PWM->CTRL |= PWM3_RESET;
		break;

	case 4:
		PWM->CTRL |= PWM4_RESET;
		break;
	}

	/* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set the dithering for the PWM channel
 * @param[in]   sel          PWM channel to be stopped
 * @param[in]   dithering    PWM dithering (expressed in clock cycles, max. 256)
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_SetDithering(PWM_SEL_t sel, uint8_t dithering)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << sel)))
    {
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if correct values were passed */
    if (dithering > PWM_MAX_DITHERING)
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Configure Dithering */
    PWM->HIGH[sel] &= ~(PWM_HIGH_HIGH_FRACTIONAL_Mask);
	PWM->HIGH[sel] |= dithering;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Configure the PWM channel
 * @param[in]   sel    PWM channel to be configured
 * @param[in]   cfg    configuration structure
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_Configure(PWM_SEL_t sel, const PWM_CFG_t *cfg)
{
    /* Pointer to GPIO driver */
    DRIVER_GPIO_t *gpio = &Driver_GPIO;

    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Prepare GPIO configuration */
    GPIO_PAD_CFG_t gpioCfg = {
        .pull_mode     = GPIO_PC_NO_PULL,
        .drive_mode    = GPIO_6X,
        .lpf_en        = GPIO_LPF_DISABLED
    };

#if (RTE_PWM0_EN)

    /* Configure PWM0 */
    if (sel == PWM_0)
    {
        /* Set the GPIO config as PWM0 config */
        gpioCfg.io_mode = MODE_GPIO_PWM0;
    }
#endif /* if (RTE_PWM0_EN) */

#if (RTE_PWM1_EN)

    /* Configure PWM1 */
    if (sel == PWM_1)
    {
        /* Set the GPIO config as PWM1 config */
        gpioCfg.io_mode = MODE_GPIO_PWM1;
    }
#endif /* if (RTE_PWM1_EN) */

#if (RTE_PWM2_EN)

    /* Configure PWM2 */
    if (sel == PWM_2)
    {
        /* Set the GPIO config as PWM2 config */
        gpioCfg.io_mode = MODE_GPIO_PWM2;
    }
#endif /* if (RTE_PWM2_EN) */

#if (RTE_PWM3_EN)

    /* Configure PWM3 */
    if (sel == PWM_3)
    {
        /* Set the GPIO config as PWM3 config */
        gpioCfg.io_mode = MODE_GPIO_PWM3;
    }
#endif /* if (RTE_PWM3_EN) */

#if (RTE_PWM4_EN)

    /* Configure PWM4 */
    if (sel == PWM_4)
    {
        /* Set the GPIO config as PWM4 config */
        gpioCfg.io_mode = MODE_GPIO_PWM4;
    }
#endif /* if (RTE_PWM4_EN) */

#if (RTE_PWM_SLOWCLK)

    CLK_DIV_CFG0->SLOWCLK_PRESCALE_BYTE = SLOWCLK_PRESCALE_3_BYTE;
    CLK->DIV_CFG2 |= PWM_SRC_SLOWCLK;

#endif /* if (RTE_PWM_SLOWCLK) */

    /* Configure gpio pad */
    gpio->ConfigurePad(PWM_Resources.info->default_cfg[sel]->pwm_default_GPIO_cfg.GPIO_pin, &gpioCfg);

    /* Configure PWM period */
    PWM->PERIOD[sel] = cfg->period;

    /* Configure PWM high period */
	PWM->HIGH[sel] &= ~(PWM_HIGH_HIGH_Mask);
	PWM->HIGH[sel] |= (cfg->high_cycle << PWM_HIGH_HIGH_Pos);

    /* Configure Dithering */
    PWM->HIGH[sel] &= ~(PWM_HIGH_HIGH_FRACTIONAL_Mask);
	PWM->HIGH[sel] |= cfg->dithering;

	if (sel != PWM_0)
	{
	    /* Configure offset */
		PWM->OFFSET[sel-1] &= ~(PWM_OFFSET_OFFSET_Mask);
	    PWM->OFFSET[sel-1] |= cfg->offset;

	    /* Enable PWM offset */
	    PWM->OFFSET[sel-1] |= PWM_OFFSET_ENABLE;
	}

    /* Indicate that PWM was Initialized */
    PWM_Resources.info->flags |= PWM_FLAG_BIT_SET << sel;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set the offset between PWM. Delay PWM(sel) with respect to PWM0
 * @param[in]   sel    PWM channel to be stopped
 * @param[in]   offset Offset between PWM (expressed in clock cycles)
 * @return      Execution status
 * @assumptions Not supported for sel = PWM0.
 */
static int32_t PWM_SetOffset(PWM_SEL_t sel, uint16_t offset)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* PWM0 and PWM(sel) must be configured before setting the offset */

    /* Check if PWM(sel) has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << sel)))
    {
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if PWM(0) has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << (0))))
    {
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if correct values were passed */
    if (PWM->PERIOD[sel] != PWM->PERIOD[0])
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    if (offset > PWM->PERIOD[sel])
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    if (sel == PWM_0)
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Configure offset */
	PWM->OFFSET[sel-1] &= ~(PWM_OFFSET_OFFSET_Mask);
    PWM->OFFSET[sel-1] |= offset;

    /* Enable PWM offset */
    PWM->OFFSET[sel-1] |= PWM_OFFSET_ENABLE;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Initializes the PWM driver
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_Initialize(void)
{

    /* Configure each enabled PWM module */
    for (int i = 0; i < PWM_PWMS_NUMBER; ++i)
    {
        /* Check if particular PWM should be initialized */
        if ((PWM_FLAG_BIT_SET << i) & PWM_EN_MSK)
        {
        	/* Reset PWM module to known state */
        	PWM->CTRL = PWM0_RESET << i;

            /* Configure particular PWM */
            PWM_Configure(i, &PWM_Resources.info->default_cfg[i]->pwm_default_cfg);

            /* Indicate that particular PWM was Initialized */
            PWM_Resources.info->flags |= PWM_FLAG_BIT_SET << i;
        }
    }

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set the period for the PWM channel
 * @param[in]   sel       PWM channel to be stopped
 * @param[in]   period    PWM period (expressed in clock cycles)
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_SetPeriod (PWM_SEL_t sel, uint16_t period)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << sel)))
    {
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if period value is within range*/
    if (period > 4096)
	{
    	return ARM_DRIVER_ERROR_PARAMETER;
	}

    /* Configure PWM period */
    PWM->PERIOD[sel] = period;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set the duty cycle for the PWM channel
 * @param[in]   sel           PWM channel to be stopped
 * @param[in]   duty_cycle    Duty cycle (expressed in percentage)
 * @return      Execution status
 * @assumptions PWM period has been already configured
 */
static int32_t PWM_SetDutyCycle(PWM_SEL_t sel, uint8_t duty_cycle)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << sel)))
    {
        /* Return driver unconfigured error */
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if correct values were passed */
    if (duty_cycle > PWM_MAX_PERCENTAGE)
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Configure PWM duty cycle */
    uint16_t cfg = PWM->PERIOD[sel] * duty_cycle / 100;
    PWM->HIGH[sel] &= ~(PWM_HIGH_HIGH_Mask);
	PWM->HIGH[sel] |= (cfg << PWM_HIGH_HIGH_Pos);

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Set the high period for the PWM channel
 * @param[in]   sel            PWM channel to be stopped
 * @param[in]   high_period    Duty cycle (expressed in clock cycles)
 * @return      Execution status
 * @assumptions PWM period has been already configured
 */
static int32_t PWM_SetHighPeriod(PWM_SEL_t sel, uint16_t high_period)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */
    if (!(PWM_Resources.info->flags & (PWM_FLAG_BIT_SET << sel)))
    {
        /* Return driver unconfigured error */
        return PWM_ERROR_UNCONFIGURED;
    }

    /* Check if high period value is not too high */
    if (high_period > PWM->PERIOD[sel])
    {
        /* Return param error */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Configure PWM high period */
	PWM->HIGH[sel] &= ~(PWM_HIGH_HIGH_Mask);
    PWM->HIGH[sel] |= (high_period << PWM_HIGH_HIGH_Pos);
	
    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start the selected PWM
 * @param[in]   sel    PWM channel to be started
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_Start(PWM_SEL_t sel)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */

    /* Enable PWM */
    PWM->CTRL |= (1 << sel);

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Stop the selected PWM
 * @param[in]   sel    PWM channel to be stopped
 * @return      Execution status
 * @assumptions None
 */
static int32_t PWM_Stop(PWM_SEL_t sel)
{
    /* Check if correct PWM was selected */
    if (!((PWM_FLAG_BIT_SET << sel) & PWM_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if PWM has been already configured */

	/* Enable PWM */
	switch (sel){

	case 0:
		PWM->CTRL |= PWM0_DISABLE;
		break;

	case 1:
		PWM->CTRL |= PWM1_DISABLE;
		break;

	case 2:
		PWM->CTRL |= PWM2_DISABLE;
		break;

	case 3:
		PWM->CTRL |= PWM3_DISABLE;
		break;

	case 4:
		PWM->CTRL |= PWM4_DISABLE;
		break;
	}
	/* Return OK */
    return ARM_DRIVER_OK;
}

/* Pwm driver control block */
DRIVER_PWM_t Driver_PWM =
{
    PWM_GetVersion,
    PWM_Initialize,
    PWM_Configure,
	PWM_SelectClock,
	PWM_Reset,
	PWM_SetDithering,
    PWM_SetPeriod,
    PWM_SetDutyCycle,
    PWM_SetHighPeriod,
    PWM_SetOffset,
    PWM_Start,
    PWM_Stop
};

#endif    /* RTE_PWM */
