
import spidev
import yaml

class SpiYAMLReader:
    def __init__(self, bus=0, device=0, max_speed_hz=500000):
        self.spi = spidev.SpiDev()
        self.bus = bus
        self.device = device
        self.max_speed_hz = max_speed_hz
        self.open()

    def open(self):
        """Open the SPI bus."""
        self.spi.open(self.bus, self.device)
        self.spi.max_speed_hz = self.max_speed_hz
        print(f"SPI bus {self.bus} device {self.device} opened with max speed {self.max_speed_hz} Hz")

    def close(self):
        """Close the SPI bus."""
        self.spi.close()
        print(f"SPI bus {self.bus} device {self.device} closed")

    def read_data_until_null(self, maxlen):
        """Read data from SPI bus until a null terminator is encountered or maxlen is reached."""
        data = []
        for _ in range(maxlen):
            byte = self.spi.readbytes(1)[0]
            if byte == 0:
                break
            data.append(byte)
        
        print(f"Read bytes from SPI until null terminator or maxlen: {data}")
        return data

    def read_yaml(self, maxlen):
        """Read YAML data from SPI bus and parse it."""
        raw_data = self.read_data_until_null(maxlen)
        try:
            yaml_string = bytes(raw_data).decode('utf-8')
            print(f"Decoded YAML string: {yaml_string}")
            yaml_data = yaml.safe_load(yaml_string)
            print(f"Parsed YAML data: {yaml_data}")
            return yaml_data
        except Exception as e:
            print(f"Error reading YAML data: {e}")
            return None

# Example usage:
# spi_reader = SpiYAMLReader(bus=0, device=0)
# yaml_data = spi_reader.read_yaml(maxlen=256)  # Specify the maximum length
# print(yaml_data)
# spi_reader.close()
