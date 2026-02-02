/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright (c) 2025-2026 University of Bristol
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/******************************************************************************/
#include <zephyr/types.h>
#include <stddef.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/kernel.h>

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
/******************* ADC Configuration and Data Structures ********************/
/**
 * Use this block to configure the ADC / sensor reading worker
 * - Define the sampling period (30 sec)
 * - Define the ADC channel from device tree
 * - Define the sensor reading worker
 * - Define any other ADC-/Sensor-related variables that may be needed
 */
#define ADC_SAMPLING_PERIOD_MS        5000

/* ADC channel from devicetree node */
static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

static int16_t adc_buf;
static bool adc_setup_done;

/* ADC peridic sampling worker*/
static struct k_timer sample_timer;
static struct k_work sample_work;
/******************* LED Configuration and Data Structures ********************/
/**
 * Use this block to configure the LED
 * - Define the LED Node alias
 * - Define the gpio device tree spec
 */
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
/******************* BLE Configuration and Data Structures ********************/
/**
 * Use this block to define BLE functionality
 * - Define the device name, configurable from prj.conf
 * - Define the COMPANY ID for the Manufacturer Specific Data element
 * - Define the format of the MSD payload, and a variable to hold it
 * - Define the format of your payload
 * - Define the advertising interval and other BLE parameters
 */
/* BLE device name, configuirable in prj.conf */
#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

/* This is the company ID that will be in the Manufacturer Specific Data */
#define COMPANY_ID 0x0059 /* Nordic Semiconductor ASA */
#define GROUP_ID 0xFF

/* Define the format of the Manufacturer Specific advertisement element */
struct adv_mfg_data {
	uint16_t company_id;
	uint8_t group_id;
	int16_t temperature;
	int32_t voltage;
} __packed;
typedef struct adv_mfg_data adv_mfg_data_t;

/* Initialise the Manufacturer Specific Data advertisement element */
static adv_mfg_data_t adv_mfg_data = {
	.company_id = COMPANY_ID,
	.group_id = GROUP_ID,
	.temperature = 0,
	.voltage = 0,
};

/**
 * Our advertisement data structure.
 * 
 * - The first element (AD0) is of type 'Complete Local Name' (x09)
 * - The second element (AD1) is Manufacturer Specific Data (0xFF)
 *   The sub-format of this field is specified in struct adv_mfg_data
 */
static const struct bt_data ad[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
	BT_DATA(BT_DATA_MANUFACTURER_DATA, (uint8_t *)&adv_mfg_data, sizeof(adv_mfg_data)),
};

/**
 * Define advertising interval (in units of 0.625 ms)
 * 
 * For example, 0x1F40 = 8000 * 0.625 ms = 5000 ms (5s)
 */
#define BT_ADV_INTERVAL 0x1F40

/* BLE advertisement parameters */
static const struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	BT_LE_ADV_OPT_NONE,
	BT_ADV_INTERVAL,
	BT_ADV_INTERVAL,
	NULL
);
/******************************************************************************/
/**
 * Use this block to define the functions needed to read the sensor
 * - A function that reads the sensor
 *   The function must turn the LED on at the start, and turn it back off if
 *   it ends successfully. In this scenario, the user will see a quick blink.
 *   If an error occurs, the LED will remain on.
 * 
 * - The sensor reading worker.
 *   When the worker has read the sensor successfully, it must update the
 *   correct part of the BLE advertisement payload.
 */
/* 
 * Read ADC once, convert to temperature and populate the arguments
 */
static int read_sensor(float *out_temp_c, int32_t *out_voltage)
{
	return 0;
}
/* Runs in system workqueue thread context (safe for adc_read) */
static void sample_work_handler(struct k_work *work)
{
	ARG_UNUSED(work);
}
/* Runs in timer context: do NOT call adc_read here */
static void sample_timer_handler(struct k_timer *timer)
{
	ARG_UNUSED(timer);
}
/******************************************************************************/
int main(void)
{
	int err;

	printk("Starting LED/ADC/BLE Advertiser Demo\n");

	/* Initialize LED0 */

	/* Start the ADC periodic sampling worker */

	/* Initialize the Bluetooth Subsystem */

	return 0;
}
