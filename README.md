#  Escáner de Puertos TCP en C
 Se trata de una herramienta con interfaz en línea de comandos para el escaneo no bloqueante de puertos TCP en redes IPv4.

---

# Características principales

* **Escaneo no bloqueante:** Utiliza la API de Windows Sockets en modo no bloqueante para determinar el estado del puerto.
* **Procesamiento de datos:**
  * **Ordenamiento:** Implementación del algoritmo *Bubble Sort* para ordenar los puertos abiertos encontrados.
  * **Búsqueda eficiente:** Implementación de *Búsqueda Binaria*  para verificar la presencia de un puerto específico dentro de los resultados escaneados.
* **Control de errores:** Validaciones de rangos de puertos, límites de memoria y manejo seguro de sockets.

---

# Tecnologías y Librerías

* **Lenguaje:** C
* **SO Compatible:** Windows
* **Librería de red:** `Winsock2` (`ws2_32.lib`)
* **Compilador probado:** MSVC (Visual Studio) 

---

## Compilación y Ejecución

###  Visual Studio (Recomendado)
1. Abrir el archivo de solución .sln en Visual Studio.
2. Asegurarse de que la librería esté vinculada (el código ya incluye #pragma comment(lib, "ws2_32.lib") ).
3. Compilar en modo  **Debug** (Ctrl + Shift + B).
4. Ejecutar con F5 o Ctrl + F5.
