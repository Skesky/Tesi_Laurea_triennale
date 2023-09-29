import pandas as pd
import matplotlib.pyplot as plt

# Leggi file CSV
data = pd.read_csv('coherent_states.csv')

# Estrai i dati dalle colonne del file CSV
distributions = data['State']
q_components = data['Real']
p_components = data['Imag']

# Crea un nuovo grafico ed inserisco dati nel grafico
plt.figure(figsize=(10, 10))
plt.scatter(q_components, p_components, s=0.03) # s=num rappresenta la dimensione dei pallini su grafico

# Aggiungi assi passanti per zero per leggibilita'
plt.axhline(y=0, color='k', linestyle='--')
plt.axvline(x=0, color='k', linestyle='--')

# Etichette e titoli
plt.xlabel('Real')
plt.ylabel('Imag')
plt.title('Stati Coerenti')
plt.grid(True)

# Mostra il grafico
plt.show()
