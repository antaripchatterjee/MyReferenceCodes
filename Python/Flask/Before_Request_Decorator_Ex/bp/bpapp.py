from flask import Blueprint, make_response

bp = Blueprint('img_bp', __name__)


@bp.before_request
def before_request():
	print('This is bp.before_request')

@bp.before_app_request
def before_app_request():
	print('This is bp.before_app_request')

@bp.route('/')
def bp_home():
	return make_response('<h1>Route Page</h1>', 200)