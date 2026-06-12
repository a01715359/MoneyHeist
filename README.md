# Money Heist
Necesitas dinero. Mucho dinero, ¿y qué mejor que conseguirlo en poco tiempo?
Money Heist es un juego de toma de decisiones en consola donde el jugador, junto con su cómplice remoto Rodrigo (The Professor), ejecuta un robo al banco VaultCore. 

Cada decisión afecta el estado del personaje: puntos de vida (HP), nivel de sospecha y recursos disponibles. Al empezar el juego, el usuario tendrá la opción de elegir dos armas de 4 (silenced pistol, dagger, electric taser, blinding powder). El objetivo es escapar con el botín antes de que la sospecha llegue al 100% o el HP caiga a 0.

# Instrucciones y consideraciones
Descarga los archivos y corre el programa en la terminal. El programa solo corre en la consola y esta hecho con c++ standard por lo que corre en todos los sistemas operativos.

Añade la información del artículo que desees, sin embargo, recuerda asegurarte de ingresar de forma correcta el tipo de dato.

Compilar con: ´g++ main.cpp -o main´

Correr en linux: ´main.out´

Correr en Windows: ´./main.exe´

### Casos en los que el proyecto dejaría de funcionar
- Como no hay destructores el comportamiento es indefinido y probablemente solo se liberará la parte de la clase base, no la de la clase derivada.
- Si el usuario intenta ingresar como su nombre, algo que involucre espacios, porque solo aceptará una única palabra.
- El usuario puede ingresar un número como su nombre, seguirá siendo considerado string. Esto lo quise dejar de esta forma, porque por temas de “privacidad” el ladrón (usuario) puede no querer revelar su verdadero nombre a Mar, por lo que peude usar un apodo.
- En caso de que el usuario ingrese un dato que no sea de tipo entero en alguno de los menús numéricos (por ejemplo letras o símbolos cuando se espera un número), std::cin entrará en estado de error y el programa podría quedarse atrapado en ciclos de validación o dejar de funcionar correctamente, ya que no se limpia el flujo de entrada.
- El usuario puede seleccionar la misma herramienta dos veces al inicio de la partida. Esto en sí no crea un error, pero si afecta en la dinámica del juego. Por ejemplo, en el menú para tomar una decisión, mostraría "1. dagger" y "2. dagger", lo cual lo vuelve un poco confuso.
- Si por algún error una herramienta consume más usos de los que posee, el atributo uses podría llegar a valores negativos porque la función consumeUse() no verifica límites antes de restar usos.
