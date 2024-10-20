/*
 * GPS_interface.h
 *
 * Created: 10/15/2024 12:42:46 AM
 *  Author: yahia
 */ 


#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_


void GPS_Init(void);
void GPS_Send(const char* command);
void GPS_Process(void);
uint8 GPS_ValidateChecksum(char* sentence);
void GPS_ParseNMEA(char* nmea);
void GPS_Parse_NEMA_modified(uint8 *nmea ,uint8 * lon , uint8 * lat) ;
void Format_Coordinates(const uint8 * lat , const uint8 * lon , uint8 * formatted_lat, uint8 * formatted_lon);

#endif /* GPS_INTERFACE_H_ */