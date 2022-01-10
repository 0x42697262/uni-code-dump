from __future__ import annotations
from abc import ABC, abstractmethod

class Command(ABC):
    @abstractmethod
    def execute(self):
        pass
    @abstractmethod
    def undo(self):
        pass
    @abstractmethod
    def __str__(self):
        pass

class Receiver:
    def __init__(self, mana:int, hp:int):
        self.__mana = mana
        self.__hp = hp

    def heal(self, value:int):
        self.__hp += value
        print(f"{self.__hp-value}(+{value}) HP")

    def meditate(self, value:int):
        self.__mana += value
        print(f"{self.__mana-value}(+{value}) MP")

    def full_recovery(self, hp_value:int, mp_value:int):
        self.__hp += hp_value
        self.__mana += mp_value
        print(f"{self.__hp-hp_value}(+{hp_value}) HP, {self.__mana-mp_value}(+{mp_value}) MP")

    def stats(self) -> int:
        return [self.__mana, self.__hp]

    def copy(self) -> Receiver:
        return Receiver(self.__mana, self.__hp)

    def restore(self, backup):
        self.__mana = backup.stats()[0]
        self.__hp = backup.stats()[1]


class Heal(Command):
    def __init__(self, param, receiver):
        self.__param = param
        self.__receiver = receiver
        self.__backup = receiver.copy()

    def execute(self):
        self.__receiver.heal(self.__param)

    def undo(self):
        self.__receiver.restore(self.__backup)

    def __str__(self):
        return(f"Healed +{self.__param} HP to {self.__receiver}.")


class Meditate(Command):
    def __init__(self, param, receiver):
        self.__param = param
        self.__receiver = receiver
        self.__backup = receiver.copy()

    def execute(self):
        self.__receiver.meditate(self.__param)

    def undo(self):
        self.__receiver.restore(self.__backup)

    def __str__(self):
        return(f"Regenerated +{self.__param} MP to {self.__receiver}.")

class Recover(Command):
    def __init__(self, param, param2, receiver):
        self.__param = param
        self.__param2 = param2
        self.__receiver = receiver
        self.__backup = receiver.copy()

    def execute(self):
        self.__receiver.full_recovery(self.__param, self.__param2)

    def undo(self):
        self.__receiver.restore(self.__backup)

    def __str__(self):
        return(f"Recovered +{self.__param} HP and +{self.__param2} MP to {self.__receiver}.")

class Invoker:
    def __init__(self):
        self.__commandHistory = []

    def displayHistory(self):
        for _ in self.__commandHistory:
            print(_)

    def invokeHeal(self, param, receiver):
        command = Heal(param, receiver)
        command.execute()
        self.__commandHistory.append(command)

    def invokeMeditate(self, param, receiver):
        command = Meditate(param, receiver)
        command.execute()
        self.__commandHistory.append(command)

    def invokeRecover(self, param, param2, receiver):
        command = Recover(param, param2, receiver)
        command.execute()
        self.__commandHistory.append(command)

    def undoPreviousCommand(self):
        undoneCommand = self.__commandHistory.pop()
        undoneCommand.undo()


if __name__ == '__main__':
    i = Invoker()

    ricky = Receiver(130, 210)
    martin = Receiver(90, 90)

    i.invokeHeal(30, ricky)
    print(ricky.stats())
    print()
    i.invokeMeditate(10, ricky)
    print(ricky.stats())
    print()
    i.invokeRecover(100, 100, martin)
    print(ricky.stats())

    print()
    i.displayHistory()

    print()
    i.undoPreviousCommand()
    i.displayHistory()
    print(ricky.stats())
    print(martin.stats())
