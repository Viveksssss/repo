from openai import OpenAI

# 初始化客户端
client = OpenAI(api_key="sk-c00cfaa72bbc4ff8b6282a39dcd54a2c", base_url="https://api.deepseek.com")

# 定义系统提示
messages = [
    {"role": "system", "content": "You are a helpful assistant"},
]

# 循环提问
while True:
    # 获取用户输入
    user_input = input("你: ")

    # 如果用户输入 "exit"，退出循环
    if user_input.lower() == "exit":
        print("对话结束。")
        break

    # 将用户输入添加到对话历史
    messages.append({"role": "user", "content": user_input})

    # 发送请求
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=messages,
        stream=False
    )

    # 获取 AI 的回答
    ai_response = response.choices[0].message.content
    print("AI:", ai_response)

    # 将 AI 的回答添加到对话历史
    messages.append({"role": "assistant", "content": ai_response})
