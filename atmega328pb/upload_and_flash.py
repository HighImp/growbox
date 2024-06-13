import paramiko
from scp import SCPClient
from pathlib import Path

# Configuration variables
REMOTE_IP = "192.168.178.16"  # Replace with the actual IP address of the remote computer
REMOTE_USER = "pi"
REMOTE_PATH = "/home/pi"     # Target directory on the remote computer
LOCAL_FOLDER = r".pio/build/ATmega328PB" # Folder containing the source file
LOCAL_FILE = "firmware.hex"

REMOTE_COMMAND = "sudo avrdude/build_linux/src/avrdude -c rasp_gpio -p m328pb -U flash:w:firmware.hex :i"
# Create a full path to the local file
local_file_path = Path(__file__).resolve().parent / Path(LOCAL_FOLDER) / LOCAL_FILE

print(Path(__file__).resolve().parent / Path(LOCAL_FOLDER))
assert Path(Path(__file__).resolve().parent / r".pio" / "build").is_dir()
assert local_file_path.is_file()

def create_ssh_client(server, user):
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect(server, username=user)
    return client

try:
    # Create SSH client
    ssh_client = create_ssh_client(REMOTE_IP, REMOTE_USER)

    # SCP transfer
    with SCPClient(ssh_client.get_transport()) as scp:
        print(f"Transferring {local_file_path} to {REMOTE_USER}@{REMOTE_IP}:{REMOTE_PATH}")
        scp.put(str(local_file_path), REMOTE_PATH)
        print("File transferred successfully.")

    # Execute remote command
    print(f"Executing command on the remote computer: {REMOTE_COMMAND}")
    stdin, stdout, stderr = ssh_client.exec_command(REMOTE_COMMAND)
    print(stdout.read().decode())
    error = stderr.read().decode()
    if error:
        print(f"Error executing the command on the remote computer: {error}")
    else:
        print("Command executed successfully.")

finally:
    ssh_client.close()
