/**
 * Author: Haoyuan Xia
 * Updated: 2018.06
 */

#define BUTTON 2
#define METERING 8
#define SHUTTER 9
#define VALVE 10

#define TEST_DROP_SIZE 30
#define TEST_DROP_COUNT 5
#define TEST_DROP_DELAY 1000
#define TEST_DROP_INTERVAL 1000
#define WATER_DROP_1 30
#define WATER_DROP_2 30

String command = "";

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(BUTTON, INPUT);
	pinMode(METERING, OUTPUT);
	pinMode(SHUTTER, OUTPUT);
	pinMode(VALVE, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:
	while (Serial.available() > 0)
	{
		command += char(Serial.read());
		delay(2);
	}
	if (command.length() > 0)
	{
		if (command.equals("t"))
		{
			test();
		}
		else if (command.equals("1"))
		{
			start1();
		}
		else if (command.equals("2"))
		{
			start2();
		}
		command = "";
	}
	digitalWrite(VALVE, digitalRead(BUTTON));
}

void test()
{
	delay(TEST_DROP_DELAY);
	for (int i = 0; i < TEST_DROP_COUNT; i++)
	{
		digitalWrite(VALVE, HIGH);
		delay(TEST_DROP_SIZE);
		digitalWrite(VALVE, LOW);
		Serial.println("Tested " + String(i + 1) + "/" + String(TEST_DROP_COUNT));
		delay(TEST_DROP_DELAY);
	}
}

void start1()
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 3; j++)
		{
			shoot();
			delay(i * 10);
			drop(WATER_DROP_1);
			Serial.println("Shoot > Delay " + String(i * 10) + " ms > Drop");
			delay(5000);
		}
	}

	for (int i = 0; i <= 0; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			drop(WATER_DROP_1);
			delay(i * 10);
			shoot();
			Serial.println("Drop > Delay " + String(i * 10) + " ms > Shoot");
			delay(5000);
		}
	}

	Serial.println("Finished");
}

void start2()
{
	for (int i = 45; i <= 70; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			shoot();
			delay(j * 5);
			drop(WATER_DROP_1);
			delay(i);
			drop(WATER_DROP_2);
			Serial.println("Shoot > Delay " + String(j * 5) + " ms > Drop > Delay " + String(i) + " ms > Drop");
			delay(5000);
		}
	}
}

void drop(int dropSize)
{
	digitalWrite(VALVE, HIGH);
	delay(dropSize);
	digitalWrite(VALVE, LOW);
}

void shoot()
{
	digitalWrite(METERING, HIGH);
	digitalWrite(SHUTTER, HIGH);
	delay(10);
	digitalWrite(SHUTTER, LOW);
	digitalWrite(METERING, LOW);
}
