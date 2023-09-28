class Exchange:
    # implement this!

    def __init__(self, initialBalance):
        """Initial Balance is the amount that each account should start with."""
        self.balance = initialBalance
        self.pendingTrades = {}
        self.pastTrades = {}
        self.cycle = 0


    def add_trade(self, trade):
        """Adds a trade to the exchange (validation required)
        and returns a match if required. It is up to you on how you will
        handle representing trades. """
        self.cycle += 1
        self.balance += trade.value
        self.pendingTrades.append(trade)
        for t in self.pendingTrades: #loop through all the pending trades
            if self.cycle - t.addTime > t.processTime: #if we reach the process time for trades
                self.pendingTrades.remove(t)
                self.pastTrades.append(t) 


