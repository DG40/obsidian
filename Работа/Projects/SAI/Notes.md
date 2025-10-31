Мои пароли на учётках: 123456 (лучше поменять на свои)
Есть 2 стенда для разработки:
* 10.110.2.144 - фронтендерский стенд SAI
* 10.110.2.58 - dev-стенд SAI, на который можно лить сборки
Ещё есть два тестовых стенда TCS (на astra и debian)
* 10.110.2.145
* 10.110.2.146 (неактивен, но наш, можно юзать)
Для входа в tcs:
melechko (вводится и для инсталляции)
1234567


"
тксы
KLM111-B9C1-49CD-F5F6  - для TCS 10.110.2.145
KLM112-6EDB-3A71-2A83 -  для TCS 10.110.2.146
  
ну в любом случае, думаю что всегда надо переустанавливать ибо сборки специальные.  
В принципе, команда должна работать  
sudo apt install -yq ./trueconf-server-name.deb  
  
Если возникают проблемы, то можно удалить через  
sudo apt purge trueconf-server  
и переустановить сервак  
  
Вот инструкции  
[https://trueconf.ru/blog/baza-znaniy/kak-za-15-minut-razvernut-sistemu-videokonferenczij-na-baze-os-linux](https://trueconf.ru/blog/baza-znaniy/kak-za-15-minut-razvernut-sistemu-videokonferenczij-na-baze-os-linux)  
[https://trueconf.ru/blog/baza-znaniy/kak-obnovit-trueconf-server](https://trueconf.ru/blog/baza-znaniy/kak-obnovit-trueconf-server)

"

Jenkins, что мне нужно (я отметил себе в Favorites):
1.0.1 Web API
1.0.0 Database Upload

Две службы:
trueconf-ai-api
trueconf-ai-db

/etc/systemd/system - лежат файлы этих служб

БД по умолчанию не позволяет удалённо подключиться. Для удалённого подключения:
cd /opt/trueconf/ai-server
cd etc/database
там 2 файла:
* pg_hba.conf
* postgresql.conf

В файле pg_hba.conf изначально нет этой фразы:
* host all all 0.0.0.0/0 trust
Можно вставить на dev-стенде, чтобы удалённо подключиться
А в файле postgresql.conf в конце строку:
* listen_addresses = '*'
Потом sudo systemctl restart trueconf-ai-db

Extentions в VSCode:
* Database Client (какая-то из двух):
	* https://open-vsx.org/extension/cweijan/vscode-database-client2
	* https://open-vsx.org/extension/cweijan/dbclient-jdbc


goland - среда для golang, если интересно



Сборка в Jenkins:
* CustomBuild - кастомная директория на fruit, если мне так надо
* git_git_gitlab_trueconf_com_products_speech2text_web_api_git - ветка для сборки (main или кастомная)
* Выбрать release или debug в зависимости от того, что хотим собрать


**БАГ**
В запросе на создание/обновление провайдера вылетает ошибка, связанная (скорее всего) с неподдержанным эндпоинтом (короче версия TCS)

__________________

Андрей Шкунов, [23.10.2025 17:42]  
openssl - утилита для работы с tls-сертификатами. понадобится при работе с лицензиями и при работе с https  
  
[23.10.2025 17:43]  
https://op.trueconf.com/projects/3/?jump=home  
  
[23.10.2025 18:38]  
https://github.com/spf13/viper  
  
[23.10.2025 18:46]  
https://habr.com/ru/articles/555920/  
  
[23.10.2025 19:01]  
тксы  
KLM111-B9C1-49CD-F5F6  
KLM112-6EDB-3A71-2A83  
  
ну в любом случае, думаю что всегда надо переустанавливать ибо сборки специальные.  
В принципе, команда должна работать  
sudo apt install -yq ./trueconf-server-name.deb  
  
Если возникают проблемы, то можно удалить через  
sudo apt purge trueconf-server  
и переустановить сервак  
  
Вот инструкции  
https://trueconf.ru/blog/baza-znaniy/kak-za-15-minut-razvernut-sistemu-videokonferenczij-na-baze-os-linux  
https://trueconf.ru/blog/baza-znaniy/kak-obnovit-trueconf-server  
  
[23.10.2025 19:04]  
бд https://builder.trueconf.com/view/Speech%20To%20Text/view/TrueConf/job/ai_server_upload_db_100/  
  
[23.10.2025 19:04]  
апи https://builder.trueconf.com/view/Speech%20To%20Text/view/TrueConf/job/ai_server_web_api_101/  
  
[23.10.2025 19:10]  
host all all 0.0.0.0/0 trust  
  
[23.10.2025 19:12]  
listen_addresses = '*'  
  
[23.10.2025 19:14]  
https://open-vsx.org/extension/cweijan/vscode-database-client2  
  
[23.10.2025 19:14]  
https://open-vsx.org/extension/cweijan/dbclient-jdbc  
  
[23.10.2025 19:20]  
репа с конфигами  
  
https://gitlab.trueconf.com/products/speech2text/extconfig

Андрей Шкунов, [24.10.2025 13:05]  
![[pam (2).c]]
это сишный исходник про авторизацию админов саи через учётки в линухе  
  
собирать вот так: gcc pam.c -lpam -lpam_misc -o pam_auth  
  
запускать через судо  
  
[24.10.2025 13:05]  
https://team.trueconf.com/files/5b542f372cd2716fc78f35a8b083dbd98f0566ba  
  
[24.10.2025 13:21]  
только там вроде надо какие-то либы доставить, чтобы собрать это гавно  
  
[24.10.2025 13:22]  
+ хуйня не для этой версии продукта