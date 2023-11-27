#include "SenseairCO2Sensor.h"

namespace IO::Input
{
    SenseairCO2Sensor::SenseairCO2Sensor()
    {
        if (DEBUG_ENABLED) 
        {
            Serial.println("Initializing CO2...");
        }
        
        // todo - consider making these values private vars?
        softwareSerialCO2 = new SOFTWARE_SERIAL(D4, D3);
        softwareSerialCO2->begin(9600);

        if (DEBUG_ENABLED) 
        {
            if(GetCO2Raw() == -1)
            {
                Serial.println("CO2 Sensor Failed to Initialize ");
            }
            else
            {
                Serial.println("CO2 Successfully Initialized.");
                // caller should permit waiting 10 seconds
            }
        }
    }

    int SenseairCO2Sensor::GetAverageCO2(int numberOfSamplesToTake)
    {
        int successfulSamplesCounter = 0;
        int co2AsPpmSum = 0;
        for (int sample = 0; sample < numberOfSamplesToTake; sample++)
        {
            int co2AsPpm = GetCO2Raw();
            if (co2AsPpm > 300 && co2AsPpm < 10000)
            {
                successfulSamplesCounter++;
                co2AsPpmSum += co2AsPpm;
            } 
            else 
            {
                // no action
            }

            // without delay we get a few 10ms spacing, add some more
            delay(250);
        }

        if (successfulSamplesCounter <= 0) 
        {
            // total failure - todo, different failure value?
            return -5;
        }
        if (DEBUG_ENABLED)
        {
            Serial.println("# of CO2 reads that worked: " + String(successfulSamplesCounter));
            Serial.println("CO2 reads sum " + String(co2AsPpmSum));
        }
        return co2AsPpmSum / successfulSamplesCounter;
    }

    int SenseairCO2Sensor::GetCO2Raw()
    {
        while(softwareSerialCO2->available())
        {
            softwareSerialCO2->read();
        }

        const byte CO2Command[] = {0XFE, 0X04, 0X00, 0X03, 0X00, 0X01, 0XD5, 0XC5};
        byte CO2Response[] = {0,0,0,0,0,0,0};
        int datapos = -1;

        const int commandSize = 8;
        const int responseSize = 7;

        int numberOfBytesWritten = softwareSerialCO2->write(CO2Command, commandSize);

        if (numberOfBytesWritten != commandSize)
        {
            // failed to write request
            return -2;
        }

        // attempt to read response
        int timeoutCounter = 0;
        while (softwareSerialCO2->available() < responseSize)
        {
            timeoutCounter++;
            if (timeoutCounter > 10) 
            {
                // timeout when reading response - todo, different failure value?
                return -3;
            }
            delay(50);
        }

        // we have 7 bytes ready to be read
        for (int i = 0; i < responseSize; i++) 
        {
            CO2Response[i] = softwareSerialCO2->read();
            if ((CO2Response[i] == 0xFE) && (datapos == -1))
            {
                datapos = i;
            }

            if (DEBUG_ENABLED)
            {
                Serial.print(CO2Response[i], HEX);
                Serial.print(":");
            }
        }

        return CO2Response[datapos + 3] * 256 + CO2Response[datapos + 4];
    }
}