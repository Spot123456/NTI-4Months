/*
 * CFile1.c
 *
 * Created: 10/15/2024 12:39:32 AM
 *  Author: yahia
 */ 
#include "../../utilities/Avr_Reg.h"
#include "../../utilities/datatypes.h"
#include "../../COMM/UART/UART_Interface.h"
#include "GPS_config.h"
#include "GPS_private.h"
#include "GPS_interface.h"

#include <string.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// Buffer for GPS data
uint8 gpsBuffer[75];
uint8 bufferIndex = 0;
uint8 dataReady = 0;


// Initialize GPS module
// we init as a data sheet said 8-bit data, 1 stop bit ,9600 
void GPS_Init(void) {
	UART_init();
	//USART_Init(MYUBRR);
}


// this for sending command to GPS

void GPS_Send(const char* command)
{
	int i =0 ; 
	for(i=0;command[i]!='\0';i++)
	{
		UART_SendData(command[i]);
	}
}

// this for received and process the command from GPS
void GPS_Process()
{
	int8 data = UART_ReceivedData();
	if (data == '$') 
	{
		bufferIndex = 0; // we know we recived a new frame 
	} 
	if (bufferIndex< sizeof(bufferIndex)-1)
	{
		
		gpsBuffer[bufferIndex++] = data ; 
		gpsBuffer[bufferIndex] = NULL;
	}
	if(data == '\n')
	{
		
		dataReady = 1;
	}
	
}

// Validate NMEA checksum
uint8 GPS_ValidateChecksum(char* sentence) {
	char* checksum_ptr = strchr(sentence, '*');
	if (checksum_ptr == NULL) {
		return 0;
	}

	unsigned int checksum = 0;
	for (char* p = sentence + 1; p < checksum_ptr; p++) {
		checksum ^= *p;
	}

	unsigned int received_checksum;
	sscanf(checksum_ptr + 1, "%2X", &received_checksum);

	return (checksum == received_checksum);
}

// Parse NMEA sentence
void GPS_ParseNMEA(char* nmea) {
	if (GPS_ValidateChecksum(nmea)) {
		if (strstr(nmea, "$GPGGA")) {
			// Example for parsing GGA sentence
			char time[10], lat[15], lon[15], quality[2];
			sscanf(nmea, "$GPGGA,%9[^,],%14[^,],%*c,%14[^,],%*c,%1[^,]", time, lat, lon, quality);
			// Now you have time, latitude, longitude, and quality of GPS fix
			// Do something with the parsed data
		}
	}
}

// parse NEMA sentence modified

void GPS_Parse_NEMA_modified(uint8 *nmea ,uint8 * lon , uint8 * lat)
{
	// check if nmea is checksum valid 
	if (GPS_ValidateChecksum(nmea))
	{
		// if valid 
		// check The  first occurrence of a substring within a larger string
		// note the strstr() function in C is used to find the first occurrence of a substring within a larger string.
		if(strstr(nmea, "$GPGGA"))
		{
			// create some var to store (parse the needed data) we can change it later to struct ^_x
			char time[10] , lat[15], lon[15], quality[2]; 
			// look we need to get data with this example frame :
			//$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
			// this frame is nmea frame which is consists of : 
			/*
				123519 is the time in UTC (12:35:19).
				4807.038 is the latitude in the format ddmm.mmmm (48 degrees, 07.038 minutes).
				N indicates north latitude.
				01131.000 is the longitude in the format dddmm.mmmm (11 degrees, 31.000 minutes).
				E indicates east longitude.
				1 is the GPS quality indicator.
			*/
			// so we need time , lat , long and quality 
			sscanf(nmea , "$GPGGA,%9[^,],%14[^],%*c,%14[^,],%*c,%1[^,]" ,time ,lat,lon,quality);
			// which is %9[^,0] i need all number extend to 10 char to see [ , ] in your sentence
			// %*c skip this char 
			
			
		}
	}
	
}


void Format_Coordinates(const uint8 * lat , const uint8 * lon , uint8 * formatted_lat, uint8 * formatted_lon)
{
	// change the lat or lon from char to float 
	float latitude = atof(lat);
	float longitude = atof(lon);
	
	// Format to degrees, keeping original NMEA format for simplicity
	sprintf(formatted_lat , "lat: %.4f" , latitude);
	sprintf(formatted_lon, "long: %.4f" , longitude) ; 
	
}

