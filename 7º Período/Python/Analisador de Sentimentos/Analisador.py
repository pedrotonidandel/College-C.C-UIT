import pandas as pd
from nltk.tokenize import word_tokenize
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn import naive_bayes
from sklearn import metrics
import seaborn as sns
from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer
sent_analyser = SentimentIntensityAnalyzer()

df = pd.read_csv('./depression_dataset.csv')

count_row = df.shape[0]
score_vector_1 = []
for i in range(count_row):
    score = sent_analyser.polarity_scores(df.clean_text[i])
    score_vector_1.append(score['compound'])

df.loc[:,'Sentimento'] = score_vector_1
df

average = df.groupby(['is_depression'], as_index=False)['Sentimento'].mean()
mi = df.groupby(['is_depression'], as_index=False)['Sentimento'].min()
ma = df.groupby(['is_depression'], as_index=False)['Sentimento'].max()
sd = df.groupby(['is_depression'], as_index=False)['Sentimento'].std()

print("Média:")
print(average)
print()

print("Mínimo:")
print(mi)
print()

print("Máximo:")
print(ma)
print()

print("Desvio Padrão:")
print(sd)

df.drop(columns=['Sentimento'], inplace=True)
df

X_train, X_test, y_train, y_test = train_test_split(df['clean_text'], df['is_depression'], test_size=0.2, random_state=42)

vetorizador = TfidfVectorizer()

X_train_vectorized = vetorizador.fit_transform(X_train)
X_test_vectorized = vetorizador.transform(X_test)

classifier = naive_bayes.MultinomialNB()
classifier.fit(X_train_vectorized, y_train)

texto = input('Digite a frase: ')

user_input = [texto]

user_input_vectorized = vetorizador.transform(user_input)

prediction = classifier.predict(user_input_vectorized)

if prediction[0] == 1:
    print("Existe uma chance de ser depressivo.")
else:
    print("Não é considerado depressivo.")
