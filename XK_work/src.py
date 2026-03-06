import requests
from bs4 import BeautifulSoup
import os

url = "https://cloud.tencent.com/developer/article/2527648"

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/143.0.0.0 Safari/537.36",
    # "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
    # "Accept-Language": "zh-CN,zh;q=0.9",
    # "Connection": "keep-alive"
}

def scrape_web_page(target_url):
    res = requests.get(target_url, headers=headers)
    res.encoding = 'utf-8'

    if res.status_code == 200:
        soup = BeautifulSoup(res.text, "html.parser")

        title_tag = soup.find("div", class_="mod-header__title")
        title = title_tag.get_text(strip=True) if title_tag else "未命名的文章"

        arc = soup.find("div", class_="rno-markdown new-version rno-")
        if arc:
            article_text = arc.get_text(strip=True)
            filename = "wbfx.txt"

            with open(filename, 'w', encoding='utf-8') as ouf:
                ouf.write(f"标题: {title}\n")
                ouf.write(f"来源: {target_url}\n")
                ouf.write("-" * 30 + "\n\n")
                ouf.write(article_text)

            print(f"保存文件至: {os.path.abspath(filename)}")
        else:
            print("未能找到正文内容区域。")
    else:
        print(res.status_code)
    return article_text

###################################################################################
import jieba
import re
from collections import Counter
from wordcloud import WordCloud
import matplotlib.pyplot as plt

def clean_data(text):
    content = re.sub(r'[^\u4e00-\u9fa5a-zA-Z0-9]', ' ', text)
    return content

def tokenizer(text):
    words = jieba.lcut(text)
    final_words = []
    for word in words:
        word = word.strip()
        if len(word) > 1 and not word.isdigit():
            final_words.append(word)
    return final_words

def counter(words):
    word_counts = Counter(words)
    len_more_than_4 = []
    s = set(words)
    for word in s:
        if len(word) >= 4:
            len_more_than_4.append(word)

    top_10 = word_counts.most_common(10)
    for word, count in top_10:
        print(f"{word}: {count} 次")
    print("\n长度大于 4 的词一共有：", len(len_more_than_4), "个。")
    return

def words_cloud(words):
    stop_words = {'我们', '可以', '使用', '进行', '一个', '为了', '对于', '由于', '通过'}
    filtered_words = [w for w in words if len(w) > 1 and w not in stop_words]
    word_counts = Counter(filtered_words)

    wc = WordCloud(
        font_path='msyh.ttc',
        background_color='white',
        width=1000,
        height=800,
        max_words=100,
        min_font_size=20,
        max_font_size=200,
        relative_scaling=0.5
    )
    wc.generate_from_frequencies(word_counts)

    plt.figure(figsize=(10, 8))
    plt.imshow(wc, interpolation='bilinear')
    plt.axis('off')
    plt.show()

    wc.to_file("wordcloud.png")
    return



if __name__ == "__main__":
    text = scrape_web_page(url)
    cleaned_text = clean_data(text)
    words = tokenizer(cleaned_text)
    counter(words)
    words_cloud(words)


