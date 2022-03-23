# public-repo-test

## Table of Contents
- [mermaid 甘特圖](#gantt-chart-by-mermaid)
- [mermaid 程序圖](#sequence-diagram-by-mermaid)
- [mermaid 流程圖](#flow-chart-by-mermaid)

## Gantt chart by mermaid
```mermaid
gantt
    title A Gantt Diagram

    section Section
    A task           :a1, 2014-01-01, 30d
    Another task     :after a1  , 20d
    section Another
    Task in sec      :2014-01-12  , 12d
    anther task      : 24d
```

## sequence diagram by mermaid
```mermaid
sequenceDiagram
    艾莉絲->包柏: 哈摟，你好嗎？
Note right of 包柏: 包柏思考中
包柏-->艾莉絲: 我很好，謝謝！
Note left of 艾莉絲: 艾莉絲回應
艾莉絲->包柏: 最近過得怎樣？
```

## flow chart by mermaid
```mermaid
graph LR
    A[Start] --> B{Is it?};
    B -- Yes --> C[OK];
    C --> D[Rethink];
    D --> B;
    B -- No ---> E[End];
```
