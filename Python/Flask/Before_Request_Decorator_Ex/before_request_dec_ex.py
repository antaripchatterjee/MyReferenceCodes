from flask import Flask, make_response
from bp.bpapp import bp

app = Flask(__name__)
app.config['SECRET_KEY'] = 'Is this a secret key?'
app.register_blueprint(bp, url_prefix='/bp')

@app.before_request
def before_request():
	print('This is app.before_request')

@app.route('/')
def index():
	return make_response('<h1>Index Page</h1>', 200)

if __name__ == '__main__':
	app.run()