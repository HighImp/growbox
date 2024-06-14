


from install_requirements import install_packages_from_requirements
install_packages_from_requirements()

import paramiko
from scp import SCPClient
from pathlib import Path

def create_ssh_client(server, user):
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect(server, username=user)
    return client

def upload_hex(hexfile, remote_ip, remote_user, remote_path):
    
    # Create a full path to the local file
    #hexfile = Path(os.curdir).absolute() / Path(LOCAL_FOLDER) / LOCAL_FILE

    assert hexfile.is_file(), f"{hexfile} is not a file" 

    try:
        # Create SSH client
        ssh_client = create_ssh_client(remote_ip, remote_user)

        # SCP transfer
        with SCPClient(ssh_client.get_transport()) as scp:
            print(f"Transferring {hexfile} to {remote_user}@{remote_ip}:{remote_path}")
            scp.put(str(hexfile), remote_path)
            print("File transferred successfully.")
    finally:
        ssh_client.close()

def burn_hex_file(remote_ip, remote_user):
    
    try:
        # Create SSH client
        ssh_client = create_ssh_client(remote_ip, remote_user)
        REMOTE_COMMAND = "sudo avrdude/build_linux/src/avrdude -c rasp_gpio -p m328pb -U flash:w:firmware.hex :i"
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

def main(source, target, env):
    # Configuration variables
    
    firmware_hex = Path(target[0].get_abspath())
    assert firmware_hex.is_file()
    print("AAAA")
    remote_ip = "192.168.178.16"  # Replace with the actual IP address of the remote computer
    remote_user = "pi"
    remote_path = "/home/pi"     # Target directory on the remote computer
    upload_hex(firmware_hex, remote_ip=remote_ip, remote_user=remote_user, remote_path=remote_path)
    burn_hex_file(remote_ip=remote_ip, remote_user=remote_user)
    
Import("env")
env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", main)