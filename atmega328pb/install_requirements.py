import subprocess
import sys

def install_packages_from_requirements():
    file_path = 'requirements.txt'
    try:
        with open(file_path, 'r') as file:
            packages = file.readlines()

        packages = [package.strip() for package in packages if package.strip()]

        for package in packages:
            subprocess.check_call([sys.executable, "-m", "pip", "install", package])
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    install_packages_from_requirements()
