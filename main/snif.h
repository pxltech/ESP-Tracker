/****************************************
 * Wifi Tracker	- Sniffer function		*
 * Sparkfun ESP32 Thing					*
 * (c) 2017								*
 ****************************************/

void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type)
{
	const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
	const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
	const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;

	char temp[3];
	char adres[18] = "";
	char rssi[4];

	//MAC: hex to string
	for(int a = 0; a < 6; a++){
	    sprintf(temp, "%02x", hdr->addr2[a]);
	    if(a == 5){
		strcat(adres, temp);
	    }else{
		strcat(adres, temp);
		strcat(adres, ":");
	    }
	}

	int x = 0, y = 0;
	while(macTable[x][0] != 'M'){
	    x++;
	    if(x > 251)
			return;
	}

	//Check duplicates
	for(y = 0; y < x; y++){
	    if(strcmp(macTable[y], adres) == 0){
		return;
	    }
	}
	for(y = 0; y < 250; y++){
	    if(strcmp(APTable[y], adres) == 0){
			strcpy(&APflag[x][0], "1");
	    }
	}
	
	//Copy MAC and RSSI in tables
	strcpy(&macTable[x][0], adres);

	sprintf(rssi, "%02d", ppkt->rx_ctrl.rssi);
	strcpy(&rssiTable[x][0], rssi);

	//Clear Terminal
	//printf("\033c");

	//Merging into 1 2D array
	char totalTable[250][26];
	
	int i = 0, j = 0;
	for(i = 0; i < x+1; i++){
	    strcpy(&totalTable[x][0], &macTable[x][0]);
	    strcat(&totalTable[x][0], " ");
	    strcat(&totalTable[x][0], &rssiTable[x][0]);
	    strcat(&totalTable[x][0], "   ");
	    strcat(&totalTable[x][0], &APflag[x][0]);
	}

	printf("|*******MAC********RSSI**AP|\n");
	for (i = 1; i < x+1; i++) {
	    printf(" ");
        for (j = 0; j < 25; j++) {
            printf("%c", totalTable[i][j]);
        }
        printf("\n");
    }

	printf("\nAantal toestellen: %d.\n", x);
}
