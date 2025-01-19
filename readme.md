# 1. git clone git@github.com:LRL52/CS144-Sponge.git
# 2. git remote set-url origin git@github.com:fukyor/CS144-Sponge.git
![alt text](image.png)
git reset --hard 423b // 主分支指针也会跟随切换,所以适用于需要将当前分支回退到之前的提交。而checkout主分支不会跟随切换，适用于切换到之前的某个提交然后创建新分支进行开发，或者仅仅是查看之前的某个提交的工作区情况。
git push --force
![alt text](image-3.png)
git checkout 898f 
git branch -d master
![alt text](image-4.png)
git branch master
![alt text](image-5.png)

# 3. 将readme.md放入工作区
![alt text](image-6.png)

# 4. 将readme.md提交到master分支
git add .

git commit -m "init"
![alt text](image-7.png)

# 5. 将master分支移动到最新提交init上
git checkout ee009

git branch -d master

git branch master
![alt text](image-8.png)

