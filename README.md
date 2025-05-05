# 🏦 C++ Banking System

A C++ console application that simulates core banking functionalities for both **savings** and **checking** accounts. Designed for academic use or small simulations, this program demonstrates file handling, class inheritance, and real-world banking logic such as interest accrual, overdraft penalties, and service fees.

<br>

## 🔍 Key Highlights

- **Account Types:** Supports both savings and checking accounts, each with tailored rules.
- **Realistic Rules:** Includes inactivity thresholds, overdraft fees (RM5 for checking accounts), and account activation limits (e.g., RM25 minimum for savings).
- **Automated Monthly Processing:** Applies interest, calculates charges, and resets monthly counters.
- **Console-Based UI:** Simple menu-driven interface for easy navigation and use.
- **File-Based Data:** Reads from and writes to `customer.txt` for persistent storage.

<br>

## 💼 Technologies Used

- **C++ (OOP Concepts):** Inheritance, encapsulation, and class structure.
- **File I/O:** Uses `ifstream` and `ofstream` for handling account data and logs.
- **Modular Codebase:** Clean class separation for future extensions or upgrades.

<br>

## 📂 Project Files

| File               | Purpose                                                       |
|--------------------|---------------------------------------------------------------|
| `BankingSystem.cpp` | Source code with full implementation of the banking logic     |
| `customer.txt`      | Input file containing account details  |


<br>

## ⚙️ How to Run

```bash
g++ BankingSystem.cpp -o banking
./banking
```
Make sure the customer.txt file is in the same directory as the executable.


<br>

## 👨‍💻 Developers
- Koh Su Xuan
- Ong Yi Yan
- Tang Yan Qing
- Saad Kabir Uddin
