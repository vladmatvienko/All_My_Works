# Диаграмма конечного автомата BrickGame Tetris

Диаграмма описывает состояния библиотеки `src/brick_game/tetris` и переходы,
которые происходят после пользовательского ввода или таймера.

```mermaid
stateDiagram-v2
    [*] --> Start
    Start --> Spawn: Start
    Spawn --> Moving: фигура создана
    Spawn --> GameOver: spawn collision
    Moving --> Moving: Left / Right / Action
    Moving --> Attaching: Down hard drop
    Moving --> Shifting: timer
    Shifting --> Moving: можно опустить на 1 клетку
    Shifting --> Attaching: земля или блок снизу
    Attaching --> Spawn: блок закреплен, верх не задет
    Attaching --> GameOver: блок закреплен в верхнем ряду
    Moving --> Paused: Pause
    Paused --> Moving: Pause
    Moving --> GameOver: Terminate
    GameOver --> Spawn: Start restart
```

## Состояния

- `Start` — игра ожидает начала партии.
- `Spawn` — выбирается текущая фигура и генерируется следующая.
- `Moving` — основной игровой режим: сдвиг, вращение и hard drop.
- `Shifting` — автоматическое падение фигуры по таймеру.
- `Attaching` — фиксация фигуры на поле, очистка линий, начисление очков.
- `GameOver` — финальное состояние партии до нового `Start`.

Пауза в коде реализована флагом `GameInfo_t.pause`, чтобы внешний API оставался
совместимым со спецификацией BrickGame.
