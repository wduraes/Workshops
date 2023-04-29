void sendTelemetry()
{
  //read light sensor and publish its value
    float Light = analogRead(A0);
    snprintf(msg, MSG_BUFFER_SIZE, "%2.2f", Light);
    if (client.publish(AIO_USERNAME "/feeds/light", msg))
    {
      Serial.print("Sending light val ");
      Serial.print(Light);
      Serial.println("...");
    }

    //read temperature sensor and publish its value
    snprintf(msg, MSG_BUFFER_SIZE, "%2.2f", mySensor.readTempC());
    if (client.publish(AIO_USERNAME "/feeds/temperature", msg))
    {
      Serial.print("Sending temperature val ");
      Serial.print(mySensor.readTempC(), 2);
      Serial.println("...");
    }

    //read humidity sensor and publish its value
    snprintf(msg, MSG_BUFFER_SIZE, "%2.2f", mySensor.readFloatHumidity());
    if (client.publish(AIO_USERNAME "/feeds/humidity", msg))
    {
      Serial.print("Sending humidity val ");
      Serial.print(mySensor.readFloatHumidity(), 2);
      Serial.println("...");
    }

    //read pressure sensor and publish its value
    snprintf(msg, MSG_BUFFER_SIZE, "%2.2f", mySensor.readFloatPressure());
    if (client.publish(AIO_USERNAME "/feeds/pressure", msg))
    {
      Serial.print("Sending pressure val ");
      Serial.print(mySensor.readFloatPressure(), 2);
      Serial.println("...");
    }

    //read altitude sensor and publish its value
    snprintf(msg, MSG_BUFFER_SIZE, "%2.2f", mySensor.readFloatAltitudeMeters());
    if (client.publish(AIO_USERNAME "/feeds/altitude", msg))
    {
      Serial.print("Sending altitude val ");
      Serial.print(mySensor.readFloatAltitudeMeters(), 2);
      Serial.println("...");
    }
}
