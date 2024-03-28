import graphviz
import matplotlib.pyplot as plt
import mglearn
import numpy as np
import pandas as pd
import pydotplus
from IPython.display import Image
from IPython.display import display
from sklearn.datasets import load_breast_cancer
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import DecisionTreeRegressor
from sklearn.tree import export_graphviz

X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]])
y = np.array([0, 1, 0, 1])
counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)

print("Частоты признаков:\n{}".format(counts))

mglearn.plots.plot_animal_tree()
plt.show()
mglearn.plots.plot_tree_progressive()
plt.show()
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42)
tree = DecisionTreeClassifier(random_state=0)
tree.fit(X_train, y_train)

print("Правильность на обучающем наборе: {:.3f}".format(
    tree.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(
    tree.score(X_test, y_test)))
tree = DecisionTreeClassifier(max_depth=4, random_state=0)
tree.fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.3f}".format(
    tree.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(
    tree.score(X_test, y_test)))
export_graphviz(tree, out_file="D:/My Files/Univer/3 COURSE/6 sem/МСХОАД/labs/lab8stuff/tree.dot", class_names=["malignant", "benign"],
                feature_names=cancer.feature_names, impurity=False, filled=True)

with open("D:/My Files/Univer/3 COURSE/6 sem/МСХОАД/labs/lab8stuff/tree.dot") as f:
    dot_graph = f.read()
graphviz.Source(dot_graph)
"Export as pdf"
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42)
clf = DecisionTreeClassifier(max_depth=4, random_state=0, )
clf = clf.fit(X_train, y_train)
dot_data = export_graphviz(clf, out_file=None)
graph = pydotplus.graph_from_dot_data(dot_data)
graph.write_pdf("D:/My Files/Univer/3 COURSE/6 sem/МСХОАД/labs/lab8stuff/cancer.pdf")
"Create tree with using IPython"
dot_data = export_graphviz(clf, out_file=None,
                                feature_names=cancer.feature_names,
                                class_names=cancer.target_names,
                                filled=True, rounded=True,
                                special_characters=True)
graph = pydotplus.graph_from_dot_data(dot_data)
Image(graph.create_png())
tree = DecisionTreeClassifier().fit(X_train, y_train)
print("Важности признаков:\n{}".format(tree.feature_importances_))


def plot_feature_cancer(model):
    n_features = cancer.data.shape[1]
    plt.barh(range(n_features), model.feature_importances_, align='center')
    plt.yticks(np.arange(n_features), cancer.feature_names)
    plt.xlabel("Важность признака")
    plt.ylabel("Признак")
    plt.show()


plot_feature_cancer(tree)
tree = mglearn.plots.plot_tree_not_monotone()
plt.show()
display(tree)
ram_prices = pd.read_csv("D:/My Files/Univer/3 COURSE/6 sem/МСХОАД/labs/lab8stuff/ram_price.csv")
plt.semilogy(ram_prices.date, ram_prices.price)
plt.xlabel("Год")
plt.ylabel("Цена $/Мбайт")
plt.show()
data_train = ram_prices[ram_prices.date < 2000]
data_test = ram_prices[ram_prices.date >= 2000]
y_train = np.log(data_train.price)
X_train = data_train.date[:, np.newaxis]

print("X:\n{}".format(X_train))
print("y:\n{}".format(y_train))

tree = DecisionTreeRegressor().fit(X_train, y_train)
linear_reg = LinearRegression().fit(X_train, y_train)
X_all = ram_prices.date[:, np.newaxis]
pred_tree = tree.predict(X_all)
pred_lr = linear_reg.predict(X_all)
price_tree = np.exp(pred_tree)
price_lr = np.exp(pred_lr)
plt.semilogy(data_train.date, data_train.price, label="Обучающие данные")
plt.semilogy(data_test.date, data_test.price, label="Тестовые данные")
plt.semilogy(ram_prices.date, price_tree, label="Прогнозы дерева")
plt.semilogy(ram_prices.date, price_lr, label="Прогнозы линейной регрессии")
plt.legend()
plt.show()