# PalindromeWord
3、回文词
【问题描述】
回文词是一种对称的字符串，也即：一个回文词从左到右读和从右到左读得到的结果是一样的。给定任意一个字符串，通过插入若干字符，都可以变为一个回文词。我们所感兴趣的是，如何在插入最少字符的情况下，将给定字符串变为回文词。请编程实现。
例如：字符串“Ab3bd”，只需插入两个字符后就可变为回文词（“dAb3bAd”和“Adb3bdA”）
【输入数据】
输入数据第一行是一个整数N（3≤N≤5000），表示字符串的长度；第二行是一个长度为N的字符串，仅由大写字母‘A’到‘Z’、小写字母‘a’到‘z’组成，严格区分大小写。
【输出数据】
输出需要最小插入的字符数，以及形成的回文字符串。

使用vs编写，未界面化，只实现了找出最长回文子序列及其长度，为找出形成的回文字符串。