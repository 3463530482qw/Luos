import subprocess

subprocess.run(["git", "add", "."], check=True)  #添加缓存
subprocess.run(["git", "commit", "-m", "0.0.001"], check=True)  #提交更改
subprocess.run(["git", "push", "--force"], check=True)  #强制推送代码
