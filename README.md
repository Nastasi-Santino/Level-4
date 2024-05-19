# Mighty Mouse

## Integrantes del grupo

* Nastasi Santino: programador. 
* Renzo Amorbello: programador.
* Gregorio Matias Andrade: programador.

## Estructura.

Lo primero que hicimos fue crear implementaciones tanto del raton como del laberinto, para ir guardando la informacion del raton con respecto al laberinto. El primer problema que nos encontramos fue al modelar el movimiento del raton, puesto que la izquierda y derecha del raton cambia constantemente segun hacia donde mira el raton. Para resolver este problema implementamos la orientacion como informacion del raton.

Para implementar el laberinto utilizamos grafos. Creamos una estructura para guardar la informacion de un casilla, como paredes, distancia al centro, vecinos, etc.

A la hora de guardar la ubicacion de las paredes nos encontramos con otro problema, cada casilla del laberinto guarda informacion de las 4 paredes adyacentes, sin embargo, al hacerlo de esta forma, guardamos cada pared 2 veces. En terminos de memoria no es tan significante, pero la implementacion se complica un poco. A pesar de esto, decidimos mantener esta implementacion e construimos una funcion para que cada vez que se activa una pared, se activa tanto en la casilla donde se encontro como en la adyacente.

## Consideraciones y proceso del algoritmo.

En un comienzo se nos ocurrio intentar que el algoritmo funciones sin implementar las paredes, es decir, si el raton se encuentra una pared hace los calculos pertinentes y elige que hacer, sin guardar la informacion de que se encontro una pared. Lo cual resulta muy ineficaz, ya que el raton pierde toda capacidad de memoria y termina encontrandose muchas veces con un mismo obstaculo.

Primero inicializamos todas las distancias al centro suponiendo que no habia paredes, y agregamos la funcion chooseNextStep que elige al vecino con menor distancia al centro. Habiendo realizado eso teniamos en mente hacer una funcion que actualice las distancias de las distintas casillas teniendo en cuenta paredes previamente alcanzadas. Sin embargo, antes de hacer esta funcion, vimos que ya llegaba al centro en varios casos. Solamente utilizando esto, nos encontramos con 2 casos problematicos. Los ciclos cortos y los callejones sin salida. Estos dos problemas los resolvimos facilmente, para el caso del callejon sin salida, hicimos que si se encuentra en uno no solo marque la casilla final sino todo el callejon para no volver a entrar. Para el problema de los loops, pusimos que, arbitrariamente, cada vez que gira hacia la izquierda guarde la posicion en la que va a estar el raton, y si vuelve a pasar por esa casilla 3 veces en 10 pasos, entonces es un loop corto y marca la casilla. Con esto, llega al centro en mas situacion todavia.

Luego, nuestra idea fue implementar un algoritmo de floodfill para encontrar las distancia hasta el centro. Para ello utilizamos una funcion recursiva que recorre el laberinto suponiendo que no hay mas paredes de las ya encontradas. Sin embargo, tuvimos problemas para hacer que funcione esta implementacion, y al final no pudimos arreglarlo, por lo que no utilizamos la funcion.
