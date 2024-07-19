
# Tarea 3 de Diseño y Análisis de Algoritmos

En esta tarea se utilizó cmake y make para generar los comandos de compilación
por lo que es necesario tener estos programas instalados para poder
compilarla, además, la tarea solo fue testeada en Debian 12 por lo que
podría no funcionar en otras plataformas.


## Instrucciónes

Lo primero que se debe hacer es poner los archivos que se entregaron con el 
enunciado en un directorio llamado `data` ubicado en el directorio raiz de la
tarea, sin cambiarles los nombres.

- Crear un directorio llamado build en el cual generar los archivos de cmake:
```bash
mkdir build
cd build
cmake ..
```

- Compilar la tarea con make:
```bash
make
```

Esto va a generar dos ejecutables: `experimentacion1` y `experimentacion2`,
el segundo recibe dos parametros de linea de comandos el primero corresponde
a la cantidad de bits para usar en el filtro de Bloom y el segundo a la cantida
de funciones de hash, para ejecutar los archivos:
```bash
./experimentacion1
./experimentacion2 500000 15
```

Los programas van a dejar su output en los archivos `resultados1.csv` y 
`resultados2.csv` respectivamente.


