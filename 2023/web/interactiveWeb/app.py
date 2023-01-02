from flask import Flask
from markupsafe import escape

app = Flask(__name__)

@app.route('/')
def hello():
    return "<h1>Main Page</h1>"

@app.route('/user/<username>')
def show_usr_profile():
    return f'User {escape(username)}'

@app.route('/about')
def about():
    return "<p>the about page</p>"

if __name__ == '__main__':
    app.run()


