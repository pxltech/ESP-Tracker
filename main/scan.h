/****************************************
 * Wifi Tracker	- AP scanner			*
 * Sparkfun ESP32 Thing					*
 * (c) 2017								*
 ****************************************/

void scan_ap_task(void *pvParameters)
{
	uint16_t n = 0;
	int i = 0, x = 0, y = 0, k = 0;
	char APadres[18] = "";
	//for(k = 0; k < 5; k++){ 	
		wifi_ap_record_t *al;
		esp_wifi_scan_start(NULL, true);
		esp_wifi_scan_get_ap_num(&n);

		printf("Scanned %d APs \r\n", n);
		al = malloc(n * sizeof(wifi_ap_record_t));
		if (al == NULL) {
			return;
		}
		if (esp_wifi_scan_get_ap_records(&n, al) == ESP_OK) {
			for (i = 0; i < n; i++) {
				uint8_t *bi = al[i].bssid;
				printf
					("%32s (%02x:%02x:%02x:%02x:%02x:%02x) rssi: %02d\r\n",
					 al[i].ssid, MAC2STR(bi), al[i].rssi);

					sprintf(APadres, "%02x:%02x:%02x:%02x:%02x:%02x", MAC2STR(bi));
					while(APTable[x][0] != 'A'){
					    x++;
					}

					for(y = 1; y <= x; y++){
					    if(strcmp(APTable[y], APadres) == 0){
						break;
					    }
					}
					strcpy(&APTable[x][0], APadres);
					
			}
		}

		free(al);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	//}
}
