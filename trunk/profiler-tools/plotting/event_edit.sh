#!/bin/bash +x

echo Type,Events,Queue,Submit,Start,End > event_main.csv
cat $1 | grep -v Info | sed -e 's/;/,/g' | sed -e 's/Event//g' >> event_main.csv

echo Type,Events,Queue,Submit,Start,End > event_ad.csv
cat $2 | grep -v Info | sed -e 's/;/,/g' | sed -e 's/Event//g' >> event_ad.csv

