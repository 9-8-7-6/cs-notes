# Machine Learning

## Definition
*   Arthur Samuel(1959):  Field of study that gives computers the ability to learn without being explicitly programmed.
*   Tom Mitchell(1998): A computer program is said to learn from experience E with respect to some task T and some performance measure P, if its performance on T, as measured by P, improves with experience E.

## Categories

### Supervised Learning

#### Core Concept
> **"Right answers" are given during training.**

*   **Definition:** The algorithm acts like a student learning from a teacher. The training dataset includes both the **inputs (features)** and the **correct outputs (labels)**.
*   **Goal:** Learn a mapping function from input ($x$) to output ($y$) well enough to predict $y$ for new, unseen $x$.

#### Main Categories of Supervised Learning

##### 1. Regression
*   **Goal:** Predict a **continuous** valued output.
*   **Key Characteristic:** The output is a number that can take on infinite values within a range.
*   **Examples:**
    *   **Housing Prices:** Given size ($x$), predict price ($y$).
    *   **Stock Market:** Predicting future stock value.
    *   **Weather:** Predicting temperature in degrees.

##### 2. Classification
*   **Goal:** Predict a **discrete** valued output (categories/labels).
*   **Key Characteristic:** The output falls into a specific class or bucket.
*   **Examples:**
    *   **Binary Classification (0 or 1):**
        *   Spam vs. Not Spam (Email).
        *   Malignant vs. Benign (Tumor detection).
    *   **Multi-class Classification:**
        *   Handwritten digit recognition ($0, 1, \dots, 9$).
        *   Image recognition (Cat, Dog, Bird, Car).

---

### Unsupervised Learning

#### Core Concept
> **Data has no labels.**

*   **Definition:** The algorithm is given data without explicit instructions on what to do with it. There are no "right answers" provided.
*   **Goal:** Find **structure**, patterns, or relationships within the data.

#### Main Categories

##### 1. Clustering
*   **Goal:** Group similar data points together automatically.
*   **Examples:**
    *   **Market Segmentation:** Grouping customers with similar purchasing behavior.
    *   **Social Network Analysis:** Identifying communities of friends.
    *   **News Aggregation:** Grouping similar news stories from different sources.

##### 2. Dimensionality Reduction
*   **Goal:** Compress data into fewer dimensions while retaining meaningful information.
*   **Examples:**
    *   **Data Visualization:** Projecting complex high-dimensional data into 2D or 3D for human understanding.
    *   **Compression:** Reducing storage space or speeding up learning algorithms.

---

### Reinforcement Learning

#### Core Concept
> **Learning by trial and error.**

*   **Definition:** An **Agent** interacts with an **Environment** to achieve a goal.
*   **Mechanism:** The agent takes actions and receives **Rewards** (positive feedback) or **Penalties** (negative feedback).
*   **Goal:** Maximize the cumulative reward over time.
*   **Examples:**
    *   **Robotics:** Learning to walk or grasp objects.
    *   **Game Playing:** AlphaGo (Go), DeepBlue (Chess), Video games.
    *   **Autonomous Driving:** Navigating traffic and making decisions.