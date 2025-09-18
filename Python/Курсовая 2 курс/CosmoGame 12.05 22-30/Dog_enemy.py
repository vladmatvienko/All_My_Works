class Dog_enemy:

    def __init__(self, Pers_X, Pers_Y):
        self.health = 100
        self.hit_radius = 3
        self.visibility = 10
        self.Dog_X = Pers_X
        self.Dog_Y = Pers_Y

    def get_damage(self, damage):
        self.health -= damage
