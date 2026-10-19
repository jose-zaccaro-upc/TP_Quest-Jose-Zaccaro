# TP_Quest - Sistema de Misiones (Unreal Engine 5)

Este repositorio contiene la implementación y comparación de un sistema de misiones desarrollado en **Blueprints** y en **C++** dentro de Unreal Engine 5.

---

## 1. Requisitos Previos

- **Unreal Engine**: 5.6 (o versión compatible de UE5).
- **IDE**: Visual Studio 2022 (con la carga de trabajo *Desarrollo para juegos con C++*) o JetBrains Rider.

---

## 2. Instrucciones de Compilación

1. Si no existe el archivo de solución o cambiaste de versión del motor, haz clic derecho sobre `TP_Quest.uproject` y selecciona **Generate Visual Studio project files**.
2. Abre la solución **`TP_Quest.sln`** en Visual Studio.
3. Configura el modo de compilación en **`Development Editor`** y la plataforma en **`Win64`**.
4. Compila el proyecto presionando **`Ctrl + Shift + B`** (o *Compilar > Compilar solución*).
   > *Nota:* Con el editor ya abierto, también puedes compilar cambios rápidos de C++ usando **Live Coding** (`Ctrl + Alt + F11`).

---

## 3. Instrucciones para Abrir el Proyecto

1. Abre el archivo **`TP_Quest.uproject`** con doble clic o inícialo desde Visual Studio presionando **`F5`** (Iniciar depuración).
2. Espera a que el editor cargue los módulos y shaders del proyecto.

---

## 4. Ubicación de los Mapas

Los mapas del proyecto se encuentran organizados dentro de la carpeta `Content/QuestsGame`:

| Mapa | Descripción | Ubicación en Content Browser | Ubicación en Disco |
| :--- | :--- | :--- | :--- |
| **`L_Quests_Blueprints`** | Implementación del sistema de misiones mediante **Blueprints**. | `/Game/QuestsGame/Blueprints/L_Quests_Blueprints` | `Content/QuestsGame/Blueprints/L_Quests_Blueprints.umap` |
| **`L_Quests_CPP`** | Implementación del sistema de misiones mediante **C++**. | `/Game/QuestsGame/CPP/L_Quests_CPP` | `Content/QuestsGame/CPP/L_Quests_CPP.umap` |

---

## 5. Instrucciones para Probar Cada Mapa

### Pasos para Ejecutar
1. En el **Content Browser**, navega a la ruta del mapa que deseas probar (`Blueprints` o `CPP`).
2. Haz doble clic sobre el mapa (`L_Quests_Blueprints` o `L_Quests_CPP`) para cargarlo en el editor.
3. Presiona el botón **Play** en la barra superior del editor o el atajo **`Alt + P`** para iniciar en modo PIE (*Play In Editor*).

### Controles de Prueba
- **`W`, `A`, `S`, `D`**: Movimiento del personaje.
- **`Ratón`**: Control de la cámara / Vista.
- **`Espacio`**: Saltar.
- **`E`**: Interactuar con los NPCs dadores de misiones (*Quest Givers*) y recolectar/completar objetivos.

### Qué Probar en Cada Mapa
- **`L_Quests_Blueprints`**: Acércate a los personajes/actores interactivos en el mapa, presiona **`E`** para recibir las misiones, verifica que el HUD de misiones se actualice y completa los objetivos interactuando con los elementos designados mediante la lógica de Blueprints.
- **`L_Quests_CPP`**: Comprueba el flujo equivalente gestionado por las clases y componentes nativos de C++ (`QuestComponent`, `QuestCharacter`, `QuestGameModeBase`), validando la recepción, seguimiento y finalización de misiones en pantalla.
