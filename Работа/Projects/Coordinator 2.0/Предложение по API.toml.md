==В config-файле есть некоторая запутанность:==

driver_type = "tcs"
[debug.drivers.config]
  [[debug.drivers.config.entities]]
	address = "10.110.2.69"
	patametr = "admin:admin"
%% 	entity_id = "My TrueConf Server" %%
	
driver_type = "ptz"
[debug.drivers.config]
  [[debug.drivers.config.entities]]
	connection_string = "10.111.32.54"
	port = 5678
%% 	entity_id = "cam1"
	inverted = false %%
	
driver_type = "videomixer"
[debug.drivers.config]
  [[debug.drivers.config.entities]]
	address = "10.110.2.69"
	connection_string = "admin:admin"
%% 	model = "AVMatrix Shark S6"
	entity_id = "videomixer1" %%
[[debug.drivers.config.entities]]
	connection_string = "10.110.2.70:19523"
%% 	model = "AVMatrix HVS0402U"
	entity_id = "videomixer2" %%

**Предложение:**
* address - IP-адрес или путь к последовательному порту для confsystem
	* Если начитается с цифры, то это "ethernet", иначе "serial" (можно вшить в логику драйвера и не выносить в api.toml параметр connection_type)
* connection_string - номер порта для взаимодействия либо пара "логин:пароль"
	* если не содержит двоеточие, то номер порта, иначе пара для авторизации
		* проблема, если нужно управлять оборудованием, у которого есть авторизация, и она находится не на 80 порту - но, по-моему, вероятность получить такое странное оборудование на поддержку крайне мала
* **Таким образом, у нас будет только поле address, и если это IP-адрес, то будет ещё connection_string (порт либо пара "логин:пароль")**
	* Вопрос: для видеоматрицы SX-SMX47 мы ставим IP-адрес, но там тоже не нужен "connection_string" - по-сути не проблема, мы же на уровне драйвера будем писать, достаточно ли нам IP-адреса или надо выбросить ошибку "пропущен параметр connection_string для этой модели оборудования, укажите там enum[port, login:password]"

**Ответ:**
* address (IP-address / serial)
* port (optional - number)
* auth (optional - "login:password")