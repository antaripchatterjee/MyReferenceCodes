import os
from bs4 import BeautifulSoup
import requests
from collections import OrderedDict
import re

html_file = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        'weather.html'
    )
)

if not os.path.isfile(html_file):
    response = requests.get('https://weather.com/en-IN/weather/today/l/22.57,88.36?par=google&temp=c')
    if response.status_code == 200:
        with open('weather.html', 'wb') as html:
            html.write(response.content)
    else:
        print(f'{response.status_code}\n\n{response.text}')
        exit(-1)

weather_details = OrderedDict()

weather_page = open('weather.html', 'rb').read()

soup = BeautifulSoup(weather_page, 'html.parser')

main_tag = soup.find('main', id='MainContent')
# with open('main.html', 'wb') as main:
#     main.write(main_tag.prettify().encode())

sections = main_tag.find_all('section')
section_current = sections[0]

current_condition_header = section_current.find('div', class_='CurrentConditions--header--3-4zi')
location = current_condition_header.find('h1', class_='CurrentConditions--location--1Ayv3').text
weather_time = current_condition_header.find('div', class_='CurrentConditions--timestamp--1SWy5').text

weather_details['weather_location'] = location
weather_details['weather-time'] = weather_time

current_weather_condition = section_current.find('div', class_='CurrentConditions--dataWrapperInner--2h2vG')

primary_weather_condition = current_weather_condition.find('div', class_='CurrentConditions--primary--3xWnK')
current_temp = primary_weather_condition.find('span', class_='CurrentConditions--tempValue--3KcTQ').text
current_condition = primary_weather_condition.find('div', class_='CurrentConditions--phraseValue--2xXSr').text

weather_details['current-temp'] = current_temp
weather_details['current-condition'] = current_condition

secondary_weather_condition = current_weather_condition.find('div', class_='CurrentConditions--secondary--2XNLR')
spans = secondary_weather_condition.find('div', class_='CurrentConditions--tempHiLoValue--A4RQE').find_all('span', attrs={'data-testid' : True})
temp_values = [span.text for span in spans]
high_temp, low_temp = temp_values[:2]

weather_details['highes-temperature'] = high_temp
weather_details['low-temperatur'] = low_temp

weather_details['periodical-forecasts'] = []

section_forecast = sections[1]
forecasts_div = section_forecast.find('div', class_='TodayWeatherCard--TableWrapper--13jpa')
forecast_periods = forecasts_div.find_all('li', class_='Column--column--2bRa6')
for forecast_period in forecast_periods:
    a_tag = forecast_period.find('a')
    time_of = a_tag.find('h3').find('span', class_='Ellipsis--ellipsis--lfjoB').text
    temp_value = a_tag.find('div', class_='Column--temp--2v_go').find('span', attrs={'data-testid': True}).text
    perception = a_tag.find('div', class_='Column--precip--2H5Iw').find('span', class_='Column--precip--2H5Iw').text
    weather_details['periodical-forecasts'].append(
        OrderedDict(period=time_of, temperature=temp_value, perception=perception)
    )


section_details = sections[3]

hero = section_details.find('div', class_='TodayDetailsCard--hero--HySn3')
feels_like = hero.find('div', class_='TodayDetailsCard--feelsLikeTemp--2GFqN').find('span', class_='TodayDetailsCard--feelsLikeTempValue--2aogo').text

weather_details['feels_like'] = feels_like

sunrise_sunset_p_tag = hero.find('div', class_='SunriseSunset--sunriseSunsetContainer--LPkkp').find_all('p', class_='SunriseSunset--dateValue--2nwgx')
sunrise_time, sunset_time = sunrise_sunset_p_tag[:2]

weather_details['sunrise-time'] = sunrise_time.text
weather_details['sunset-time'] = sunset_time.text

details = section_details.find('div', class_='TodayDetailsCard--detailsContainer--1tqay')

details_data = details.find_all('div', class_='ListItem--listItem--1r7mf WeatherDetailsListItem--WeatherDetailsListItem--3w7Gx')

wind_direction = None
pressure_direction = None

all_values = OrderedDict()

for detail_data in details_data:
    data_for = detail_data.find('div', class_='WeatherDetailsListItem--label--3JSSI').text
    data = detail_data.find('div', class_='WeatherDetailsListItem--wxData--23DP5').find_all('span')
    if len(data) == 0:
        all_values[data_for] = detail_data.find('div', class_='WeatherDetailsListItem--wxData--23DP5').text
        continue
    for d in data:
        testid = d['data-testid']
        if testid == 'TemperatureValue':
            if data_for == 'High/Low':
                if data_for in all_values.keys():
                    all_values[data_for] += f'/{d.text}'
                else:
                    all_values[data_for] = d.text
                continue
        elif testid == 'Wind':
            wind_direction = d.find('svg')['style']   
        elif testid =='PressureValue':
            pressure_direction = d.find('svg')['name']
        all_values[data_for] = d.text

if pressure_direction == 'arrow-down':
    all_values['Pressure'] += ' Downwards'
elif pressure_direction == 'arrow-up':
    all_values['Pressure'] += ' Upwards'

pat = r'^transform\s*\:\s*rotate\s*\(\s*([\-\+]?\d+)\s*deg\s*\)\s*$'
m = re.match(pat, wind_direction, flags=re.IGNORECASE)

if m is not None:
    deg = int(m.groups()[0])
    actual_direction = deg%360
    if actual_direction < 0:
        actual_direction = 360 + actual_direction
else:
    actual_direction = None

if actual_direction is not None:
    all_values['Wind'] += f' towards {actual_direction}{chr(176)} from absolute south'
else:
    all_values['Wind'] += f' (Could not get the direction of the wind)'
weather_details['overall-details'] = all_values
            
air_qualities = OrderedDict()
for section in sections:
    air_quality = section.find('div', 'AirQuality--AirQualityCard--Ipx5M')
    if air_quality is not None:
        air_qualities['value'] = air_quality.find('text', class_='DonutChart--innerValue--k2Z7I').text
        air_qualities['severity'] = air_quality.find('span', class_='AirQualityText--severity--1VMr2').text
        air_qualities['severity-text'] = air_quality.find('p', class_='AirQualityText--severityText--3QoOU').text
        break

weather_details['air-quailities'] = air_qualities
print(weather_details)