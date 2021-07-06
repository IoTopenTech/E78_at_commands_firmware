# E78_at_commands_firmware
Versión modificada de la Release 4.4. de
Se han quitado los archivos de CN470 (tanto de los headers como de la carpeta Linkwan), y metido los de EU868 en headers y la carpeta LoRaWAN
Se quita la definición del preprocesador CONFIG_LINKWAN y se sustituye la de region CN470A por EU868

2 modificaciones que he hecho en el código fuente para que sea menos verboso

//Para evitar que el E78 sea demasiado verboso, comento esta línea
//PRINTF_RAW("\r\n%s%s:~# ", CONFIG_MANUFACTURER, CONFIG_DEVICE_MODEL);
//en el archivo linkwan_ica_at.c
//y añado este define en las definiciones del preprocesador
//CONFIG_PRINT_ECHO_DISABLE

Otra modificación para saber en el RECV si hay un uplinkNeeded



