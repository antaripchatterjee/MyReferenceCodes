# Python Package Release

This small documentation will show you, how to release a python package into [PyPi](https://pypi.org/).

## Build the distributions.

At first you have to navigate to the project directory and a valid `setup.py` has to be present inside the same directory and execute the below command.

```bash
python setup.py sdist bdist_wheel
```

To know more about the wheel distibutions, follow this [URL](https://pythonwheels.com/)

## Install twine

Execute the below command to install `twine`.

```bash
pip install twine
```
## Validating distributions

Execute the below command to check, if the distributions are valid to be uploaded.

```bash
twine check dist/*
```

You should see every check as PASSED only.

## Uploading to PyPi test environment

Before uploading to [PyPi](https://pypi.org/), we will upload the distributions of our project[Test PyPi](https://test.pypi.org/), so that we do any pre upload validations.

Make sure you have an active account in [Test PyPi](https://test.pypi.org/) and then execute the below command.

```bash
twine upload --repository-url https://test.pypi.org/legacy/ dist/*
```

Now you can navigate to `https://test.pypi.org/project/<Project>/` to check, if the upload is successful.

## Uploading to PyPi

Once every steps are done successfully, we are good to proceed with the last part i.e. uploading our project to [PyPi](https://pypi.org/), and if you do not have any active account in [PyPi](https://pypi.org), create one and finally execute the below command.

```bash
twine upload --repository-url https://upload.pypi.org/legacy/ dist/*
```
Project will be located at `https://pypi.org/project/<Project>/`.

## PIP install

You can now run the `pip` command to check if it can be downloaded. Just run the below command.

```bash
pip install <Project>
```

If you do not want it to be kept, just uninstall it by running the below command.

```bash
pip uninstall <Project>
```

## Most important

I believe, we make modules for people, so let them know. Write some blogs, make videos and solve some real time problems using your module. Solve issues in stackoverflow, github! your project will definitely get fame.