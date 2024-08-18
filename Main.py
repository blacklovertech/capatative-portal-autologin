import requests
import time

# Configuration
base_url = 'http://ip_address_of_your_login_portal/'
login_url = f'{base_url}/login.xml'
logout_url = f'{base_url}/logout.xml'
username = '#'  # Replace with your actual username
password = '#'  # Replace with your actual password

def login_to_portal():
    """Log in to the captive portal."""
    payload = {
        'mode': '191',
        'username': username,
        'password': password,
        'a': '1',  # This can be any value, often a timestamp is used
        'producttype': '0'
    }

    headers = {
        'Content-Type': 'application/x-www-form-urlencoded',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
    }

    try:
        response = requests.post(login_url, data=payload, headers=headers)
        if response.status_code == 200:
            print('Login successful!')
            print('Response:', response.text)
        else:
            print(f'Login failed with status code {response.status_code}')
            print('Response:', response.text)

    except Exception as e:
        print(f'An error occurred during login: {e}')

def logout_from_portal():
    """Log out from the captive portal."""
    payload = {
        'mode': '193',  # Mode 193 is typically used for logging out
        'username': username,
        'a': '1',  # Can be any value, often a timestamp is used
        'producttype': '0'
    }

    headers = {
        'Content-Type': 'application/x-www-form-urlencoded',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
    }

    try:
        response = requests.post(logout_url, data=payload, headers=headers)
        if response.status_code == 200:
            print('Logout successful!')
            print('Response:', response.text)
        else:
            print(f'Logout failed with status code {response.status_code}')
            print('Response:', response.text)

    except Exception as e:
        print(f'An error occurred during logout: {e}')
       
     

if __name__ == '__main__':
    # Log in to the portal
    login_to_portal()
    
    # Wait for a specified amount of time before logging out
    delay = 3600  # Delay in seconds (e.g., 3600 seconds = 1 hour)
    print(f'Waiting for {delay / 60} minutes auto before logging out...')
    time.sleep(delay)
    
    # Log out from the portal
    logout_from_portal()
