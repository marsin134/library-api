# Library API — Backend на C++ с кэшированием

**Library API** — это высокопроизводительный REST API сервис для управления библиотекой книг. Написан на современном C++17 с акцентом на многопоточность, кэширование и чистую архитектуру.

Проект создан как демонстрация навыков разработки промышленных приложений на C++: работа с PostgreSQL, Redis, HTTP-сервером Crow и системой сборки CMake.

---

## Ключевые особенности

- **REST API** на базе легковесного фреймворка Crow
- **Кэширование запросов** через Redis с настраиваемым TTL
- **Пул соединений** с PostgreSQL для эффективной работы в многопоточной среде
- **Многопоточность** — сервер обрабатывает запросы конкурентно
- **Конфигурация через JSON-файл** — никакого хардкода
- **Миграции базы данных** в SQL-файле
- **Готовность к юнит-тестированию** (Google Test)

---

## Технологический стек

| Категория      | Технология                        |
|----------------|-----------------------------------|
| Язык           | C++17                             |
| HTTP-сервер    | Crow (header-only)                |
| База данных    | PostgreSQL 16, libpqxx            |
| Кэш            | Redis 7, redis++                  |
| Сборка         | CMake 3.16+                       |
| Конфигурация   | nlohmann/json                     |
| Тестирование   | Google Test                       |
| ОС             | Linux (Ubuntu 22.04+)             |

---

## Быстрый старт

### Предварительные требования

Убедись, что у тебя установлены:

```bash
sudo apt update
sudo apt install -y build-essential cmake git
sudo apt install -y postgresql postgresql-client libpqxx-dev
sudo apt install -y redis-server libhiredis-dev libredis++-dev
sudo apt install -y libboost-all-dev
```
### Для Crow и nlohmann/json:

```bash
cd /opt
sudo git clone https://github.com/CrowCpp/Crow.git
```

### Настройка базы данных

```bash
# Создаём пользователя и БД
sudo -u postgres psql
CREATE USER library_user WITH PASSWORD 'secret_password';
CREATE DATABASE library_db OWNER library_user;
\q

# Применяем миграции
psql -U library_user -d library_db -f migrations/001_init.sql
```

### Настройка Redis

```bash 
sudo systemctl start redis-server
sudo systemctl enable redis-server
```

### Конфигурация
Отредактируй config.json под свои настройки (порты, пароли, TTL):
```bash
{
  "server": {
    "port": 8080,
    "threads": 4
  },
  "database": {
    "host": "localhost",
    "port": 5432,
    "dbname": "library_db",
    "user": "library_user",
    "password": "secret_password",
    "connection_pool_size": 10
  },
  "cache": {
    "host": "localhost",
    "port": 6379,
    "ttl_seconds": 60
  }
}
```

### Сборка

```bash 
cd /адрес вашего проекта
mkdir build && cd build
cmake ..
make -j4
```

### Запуск
```bash
./library_server
```
Сервер поднимется на http://localhost:8080.

---

## API Endpoints

#### ***GET /book/{id}*** - Получить книгу по ID.

Параметры - id (int) идентификатор книги

#### Пример запроса:

```bash
curl http://localhost:8080/book/1
```

Успешный ответ:

```json
200 OK
{
  "id": 1,
  "title": "Война и мир",
  "author": "Лев Толстой",
  "year": 1869,
  "genre": "Роман"
}
```
Если книга не найдена:

```json
404 Not Found
{
  "error": "Book not found"
}
```