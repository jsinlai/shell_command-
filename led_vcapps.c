/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "shell.h"
#include "sys/node-id.h"
#include "gpio_config.h"
#include "hal/gpio.h"

/* Note: you can rename this process as you wish */
PROCESS(vertexcom_apps_test_process, "vcapps");
AUTOSTART_PROCESSES(&vertexcom_apps_test_process);
SHELL_COMMAND(vcapps_command,
	      "vcapps",
	      "vcapps",
	      &vertexcom_apps_test_process);

void vcapps_shell_init(void)
{
    shell_register_command(&&vcapps_command);
}

PROCESS_THREAD(vertexcom_apps_test_process, ev, data)
{
    const char *param, *nextptr = data;
    int value;
    PROCESS_BEGIN();
    if ((param = shell_get_next_options(nextptr, &nextptr)) == NULL) {
        vcapps_shell_init();
        PROCESS_EXIT();
    }

    if (strcmp(param, "rxled") == 0) {
        if ((param = shell_get_next_options(nextptr, &nextptr)) != NULL) {
            if ((value = atoi(param))) {
                printf("RX LED ON port=%d pin=%d\n", RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
                hal_gpio_output_init(RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
                hal_gpio_low(RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
            } else {
                printf("RX LED OFF port=%d pin=%d\n", RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
                hal_gpio_output_init(RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
                hal_gpio_high(RADIO_HOST_RXLED_PORT, RADIO_HOST_RXLED_PIN);
            }
        }
    }

    if (strcmp(param, "txled") == 0) {
        if ((param = shell_get_next_options(nextptr, &nextptr)) != NULL) {
            if ((value = atoi(param))) {
                printf("TX LED ON port=%d pin=%d\n", RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
                hal_gpio_output_init(RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
                hal_gpio_low(RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
            } else {
                printf("TX LED OFF port=%d pin=%d\n", RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
                hal_gpio_output_init(RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
                hal_gpio_high(RADIO_HOST_TXLED_PORT, RADIO_HOST_TXLED_PIN);
            }
        }
    }
    PROCESS_END();
}

