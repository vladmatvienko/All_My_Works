# Диаграмма конечного автомата BrickGame Snake

Диаграмма описывает состояния библиотеки `src/brick_game/snake` и переходы,
которые происходят после пользовательского ввода или истечения таймера.

```mermaid
stateDiagram-v2
    [*] --> Start
    Start --> Spawn: Start
    Spawn --> Moving: начальная змейка и яблоко созданы
    Moving --> Moving: Left / Right
    Moving --> Shifting: timer / Action
    Shifting --> Moving: шаг без яблока
    Shifting --> Eating: голова попала на яблоко
    Shifting --> GameOver: столкновение со стеной или собой
    Eating --> Moving: +1 score, +1 length, spawn apple
    Eating --> GameOver: длина достигла 200
    Moving --> Paused: Pause
    Paused --> Moving: Pause
    Moving --> GameOver: Terminate
    GameOver --> Spawn: Start restart
```

## Состояния

- `Start` — ожидание начала партии.
- `Spawn` — создание начальной змейки длиной 4 и первого яблока.
- `Moving` — основной игровой режим: обработка относительных поворотов влево и вправо.
- `Shifting` — автоматический шаг змейки по таймеру или по клавише действия.
- `Eating` — обработка съеденного яблока: рост длины, очки, рекорд и уровень.
- `GameOver` — финальное состояние после проигрыша, победы или завершения игроком.

Пауза реализована флагом `GameInfo_t.pause`, чтобы внешний API оставался совместимым со спецификацией BrickGame.
