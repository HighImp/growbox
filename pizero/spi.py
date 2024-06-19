import RPi.GPIO as GPIO
import time

class BitBangSPI:
    """
    A class to represent a bit-banged SPI interface on a Raspberry Pi using RPi.GPIO.

    Attributes
    ----------
    clk : int
        GPIO pin number for the clock (CLK).
    miso : int
        GPIO pin number for the Master In Slave Out (MISO).
    mosi : int
        GPIO pin number for the Master Out Slave In (MOSI).
    cs : int
        GPIO pin number for the chip select (CS).
    delay : float
        Delay time between clock transitions, in seconds.

    Methods
    -------
    setup_gpio():
        Sets up the GPIO pins for SPI communication.
    cleanup_gpio():
        Cleans up the GPIO settings.
    spi_transfer(byte_out):
        Transfers a byte over SPI and reads a byte simultaneously.
    """
    
    def __init__(self, clk=11, miso=9, mosi=10, cs=8, delay=0.0001):
        """
        Constructs all the necessary attributes for the BitBangSPI object.

        :param clk: GPIO pin number for the clock (CLK). Default is 11.
        :param miso: GPIO pin number for the Master In Slave Out (MISO). Default is 9.
        :param mosi: GPIO pin number for the Master Out Slave In (MOSI). Default is 10.
        :param cs: GPIO pin number for the chip select (CS). Default is 8.
        :param delay: Delay time between clock transitions, in seconds. Default is 0.0001.
        """
        self.clk = clk
        self.miso = miso
        self.mosi = mosi
        self.cs = cs
        self.delay = delay
        self.setup_gpio()
    
    def setup_gpio(self):
        """
        Sets up the GPIO pins for SPI communication.
        """
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.clk, GPIO.OUT)
        GPIO.setup(self.mosi, GPIO.OUT)
        GPIO.setup(self.miso, GPIO.IN)
        GPIO.setup(self.cs, GPIO.OUT)
        
        # Set initial states
        GPIO.output(self.cs, GPIO.HIGH)
        GPIO.output(self.clk, GPIO.LOW)

    def cleanup_gpio(self):
        """
        Cleans up the GPIO settings.
        """
        GPIO.cleanup()

    def spi_transfer(self, byte_out):
        """
        Transfers a byte over SPI and reads a byte simultaneously.

        :param byte_out: The byte to be sent over SPI.
        :return: The byte received over SPI.
        """
        byte_in = 0
        GPIO.output(self.cs, GPIO.LOW)
        for bit in range(8):
            # Write bit to MOSI
            GPIO.output(self.mosi, byte_out & (1 << (7 - bit)))
            
            # Toggle clock
            GPIO.output(self.clk, GPIO.HIGH)
            time.sleep(self.delay)  # Use class delay
            
            # Read bit from MISO
            if GPIO.input(self.miso):
                byte_in |= (1 << (7 - bit))
            
            GPIO.output(self.clk, GPIO.LOW)
            time.sleep(self.delay)  # Use class delay

        GPIO.output(self.cs, GPIO.HIGH)
        return byte_in

