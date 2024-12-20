## Лаба не сложная, делается по лекции, но есть один момент

1) Если вы чет поменяли с сервисом:<br/>
```
netsh delete urlacl url=http://+:8733/Design_Time_Addresses/lab5/WCFSiplex/
```
2) Если не удается запустить заново сервис:<br/>
```
netsh http add urlacl url=http://+:8733/Design_Time_Addresses/lab5/WCFSiplex/ user=dimadd\dimat
```
user=dimadd\dimat - ваше имя (пишем в CMD whoami и вставляем)