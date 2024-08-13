#include "PlantowerPMSensor.h"

namespace IO::PM
{
    PlantowerPMSensor::PlantowerPMSensor()
    {
        if (DEBUG_ENABLED) 
        {
            Serial.println("Initializing CO2...");
        }
        
        
    }


    int PlantowerPMSensor::GetPM1_0Raw() { return 0; };
    int PlantowerPMSensor::GetPM2_5Raw() 
    { 
        int pm02;
        ParticulateMatterSample data;
        requestRead();
        if (readUntil(data)) {
            pm02 = data.PM_AE_UG_2_5;
            return pm02;
        } else {
            return -1;
        }
    };

    void PlantowerPMSensor::requestRead()
    {
        if (_mode == MODE_PASSIVE)
        {
            uint8_t command[] = { 0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71 };
            _stream->write(command, sizeof(command));
        }
    }

    // Blocking function for parse response. Default timeout is 1s.
    bool PlantowerPMSensor::readUntil(ParticulateMatterSample& data, uint16_t timeout)
    {
        _data = &data;
        uint32_t start = millis();
        do
        {
            loop();
            if (_PMSstatus == STATUS_OK) break;
        } while (millis() - start < timeout);

        return _PMSstatus == STATUS_OK;
    }

    void PlantowerPMSensor::loop()
    {
        _PMSstatus = STATUS_WAITING;
        if (_stream->available())
        {
            uint8_t ch = _stream->read();

            switch (_index)
            {
                case 0:
                if (ch != 0x42)
                {
                    return;
                }
                _calculatedChecksum = ch;
                break;

                case 1:
                if (ch != 0x4D)
                {
                    _index = 0;
                    return;
                }
                _calculatedChecksum += ch;
                break;

                case 2:
                _calculatedChecksum += ch;
                _frameLen = ch << 8;
                break;

                case 3:
                _frameLen |= ch;
                // Unsupported sensor, different frame length, transmission error e.t.c.
                if (_frameLen != 2 * 9 + 2 && _frameLen != 2 * 13 + 2)
                {
                    _index = 0;
                    return;
                }
                _calculatedChecksum += ch;
                break;

                default:
                if (_index == _frameLen + 2)
                {
                    _checksum = ch << 8;
                }
                else if (_index == _frameLen + 2 + 1)
                {
                    _checksum |= ch;

                    if (_calculatedChecksum == _checksum)
                    {
                    _PMSstatus = STATUS_OK;

                    // Standard Particles, CF=1.
                    _data->PM_SP_UG_1_0 = makeWord(_payload[0], _payload[1]);
                    _data->PM_SP_UG_2_5 = makeWord(_payload[2], _payload[3]);
                    _data->PM_SP_UG_10_0 = makeWord(_payload[4], _payload[5]);

                    // Atmospheric Environment.
                    _data->PM_AE_UG_1_0 = makeWord(_payload[6], _payload[7]);
                    _data->PM_AE_UG_2_5 = makeWord(_payload[8], _payload[9]);
                    _data->PM_AE_UG_10_0 = makeWord(_payload[10], _payload[11]);

                    // Total particles count per 100ml air
                        _data->PM_RAW_0_3 = makeWord(_payload[12], _payload[13]);
                        _data->PM_RAW_0_5 = makeWord(_payload[14], _payload[15]);
                        _data->PM_RAW_1_0 = makeWord(_payload[16], _payload[17]);
                        _data->PM_RAW_2_5 = makeWord(_payload[18], _payload[19]);
                        _data->PM_RAW_5_0 = makeWord(_payload[20], _payload[21]);
                        _data->PM_RAW_10_0 = makeWord(_payload[22], _payload[23]);

                        // Formaldehyde concentration (PMSxxxxST units only)
                        _data->AMB_HCHO = makeWord(_payload[24], _payload[25]) / 1000;

                        // Temperature & humidity (PMSxxxxST units only)
                        _data->PM_TMP = makeWord(_payload[20], _payload[21]) / 10;
                        _data->PM_HUM = makeWord(_payload[22], _payload[23]) / 10;
                    }

                    _index = 0;
                    return;
                }
                else
                {
                    _calculatedChecksum += ch;
                    uint8_t payloadIndex = _index - 4;

                    // Payload is common to all sensors (first 2x6 bytes).
                    if (payloadIndex < sizeof(_payload))
                    {
                    _payload[payloadIndex] = ch;
                    }
                }

                break;
            }

            _index++;
        }
    }

    int PlantowerPMSensor::GetPM10_0Raw() { return 0; };

    int PlantowerPMSensor::GetPM0_5Count() { return 0; };
    int PlantowerPMSensor::GetPM0_3Count() { return 0; };
    int PlantowerPMSensor::GetPM1_0Count() { return 0; };
    int PlantowerPMSensor::GetPM2_5Count() { return 0; };
    int PlantowerPMSensor::GetPM5_0Count() { return 0; };
    int PlantowerPMSensor::GetPM10_0Count() { return 0; };
}