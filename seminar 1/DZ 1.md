<script type="text/javascript"
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.0/MathJax.js?config=TeX-AMS_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    tex2jax: {
      inlineMath: [['$','$'], ['\\(','\\)']],
      processEscapes: true},
      jax: ["input/TeX","input/MathML","input/AsciiMath","output/CommonHTML"],
      extensions: ["tex2jax.js","mml2jax.js","asciimath2jax.js","MathMenu.js","MathZoom.js","AssistiveMML.js", "[Contrib]/a11y/accessibility-menu.js"],
      TeX: {
      extensions: ["AMSmath.js","AMSsymbols.js","noErrors.js","noUndefined.js"],
      equationNumbers: {
      autoNumber: "AMS"
      }
    }
  });
</script>


# ДЗ 1 Анализ алгоритмов

## Сортировка пузырьком

![alt text](image.png)

### Доказательство через инвариант

Инвариант возьмем такой:

В конце $i$-того цикла последние $i+1$ элементов стоят на своих местах (т.е. стоят так, как стояи бы в отсортированном массиве)

на 0 шаге это выполняется (в цикле по $j$ мы отправим самый больший элемент в конец)

на $i$-том шаге у нас неотсортированными остаются $n-i$ первых элементов(потому что инвариант работал на $i-1$ шаге). Максимальный из них встанет на $N-i-1$ место благодаря циклу по $j$. Инвариант выполняется.

В конце последнего шага окажется, что последние $i+1=N$ элементов отсортированны. инвариант выполняется.



## Алгоритм Шелла

![alt text](image-1.png)



### Временная оценка сложности

рассмотрим худший случай 

худший случай для 8 выглядит так:

$8,4,6,2,7,3,5,1$

Массив выстроен так, что для каждой последовательности (подстрока соседние элементы которой удалены на интервал) длины $k$ количество свопов для сортировки вставками будет равно $1+2+..+k/2=\frac{k(k/2+1)}{4}$

Каждое такое действие умножаем на $3$ (помимо свопа надо будет сделать проверку условия и уменьшить $j$)

тогда 

$T(N)=\sum^{log_2N}_1(\frac{N}{2^i}3\frac{2^{i-1}(2^{i-1}+1)}{4})\to\frac{3}{4}NlogN$