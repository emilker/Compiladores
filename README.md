# Musical Notation Parser

Este repositorio contiene un analizador de notación musical desarrollado con Bison (para análisis sintáctico) y Flex (para análisis léxico). El objetivo es interpretar un lenguaje textual para notación musical que permite definir tonalidades, secciones, compases y notas.

# Descripción
El lenguaje de entrada permite definir instrucciones musicales como:

- Firmas de tiempo, por ejemplo:

time 4/4

- Compases, por ejemplo:

F4 q, E4 q, D4 q, C4 q | G4 h, F4 q, E4 q

- Secciones y repeticiones, por ejemplo:

section Be {
    F4 q, E4 q, D4 q, C4 q | G4 h, F4 q, E4 q
}

repeat 2 {
    - q, D4 q, E4 q, F4 q | G4 h, A4 q, G4 q
}

El analizador procesa estas entradas de acuerdo a la siguiente estructura gramatical (definida en Bison)

# Explicación:
- program: El punto de entrada del analizador, compuesto por una secuencia de declaraciones (statement).
- statement: Se compone de asignaciones (definiciones de tiempo, clave o clef), secciones o compases.
- assignment: Permite definir propiedades globales de la pieza (firma de tiempo, tonalidad, clave).
- section: Define bloques musicales identificados mediante section o repeat y delimitados por llaves { ... }.
- expression: Envuelve un bloque de compases.
- compasses: Representa una secuencia de notas que puede estar separada por comas y barras (|) para indicar compases.
- note: Define una nota musical, que puede ser una nota o un descanso, con su respectiva duración. Las notas se representan por un token, opcionalmente, la octava (por ejemplo, F4).

# Cómo Compilar
Asegúrate de tener instalado Bison y Flex.

- Ejecuta el comando make en el directorio del proyecto:

make

Esto generará un ejecutable llamado, por ejemplo, validator.

- Crea un archivo de entrada de tus notas musicales (por ejemplo, notas.txt):
Luego, ejecuta el analizador

./validator nota.txt
