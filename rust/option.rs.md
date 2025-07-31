# Option.rs

## Type Option is optional value, either Some contain a value, or None does not.

- Rust does not have null references. Instead, it uses Option<T> to represent optional values

- When T is a pointer type, Option<T> is still an enum, but it may be optimized to the same size as T.

- Option can be unwrapped using the ? operator, *?*, ? unwraps Some and returns early if the value is None

- Rust guarantee to optimize the type T and Option<T> has the same size

- **is_some** and **is_none** return true if Option is **Some** or **None**

## Adapter for references

- **as_ref** convert **&Option<T>** to **Option<&T>**

- **as_mut** convert **&mut Option<T>** to **Option<&mut T>**

## Extracting the value

- **excect** panics with provided message
- **unwrap** panics with generic message
- **unwrap_or** returns the provided default value
- **unwrap_or_default** returns the default value of the type **T**

## Transform contained value

### Transform **Option** to **Result

- **ok_or** transforms **Some(v)** to **Ok(v)**, and **None** to **Err(err)**, err is default value

```Rust
let opt = Some(10);
let res = opt.ok_or("Value is missing");
assert_eq!(res, Ok(10));

let none: Option<i32> = None;
let res = none.ok_or("Value is missing");
assert_eq!(res, Err("Value is missing"));
```

- **ok_or_else** transforms **Some(v)** to **Ok(v)**, and **None** to a value of **Err** using the provided function

```Rust
let opt = Some("data");
let res = opt.ok_or_else(|| "Error: no data");
assert_eq!(res, Ok("data"));

let none: Option<&str> = None;
let res = none.ok_or_else(|| "Error: no data");
assert_eq!(res, Err("Error: no data"));
```

- **transpose** transposes an **Option** of a **Result** into a **Result** of an **Option**

```Rust
let opt_res: Option<Result<i32, &str>> = Some(Ok(42));
let res = opt_res.transpose();
assert_eq!(res, Ok(Some(42)));

let opt_res: Option<Result<i32, &str>> = Some(Err("fail"));
let res = opt_res.transpose();
assert_eq!(res, Err("fail"));

let opt_res: Option<Result<i32, &str>> = None;
let res = opt_res.transpose();
assert_eq!(res, Ok(None));
```

## These methods transform the **Some** variant:

- filter calls the provided predicate function on the contained value t if the Option is Some(t), and returns Some(t) if the function returns true; otherwise, returns None

```Rust
let opt = Some(10);
let filtered = opt.filter(|&x| x > 5);
assert_eq!(filtered, Some(10));

let filtered = opt.filter(|&x| x < 5);
assert_eq!(filtered, None);
```

- flatten removes one level of nesting from an Option<Option<T>>

```Rust
let nested = Some(Some(42));
let flat = nested.flatten();
assert_eq!(flat, Some(42));

let nested: Option<Option<i32>> = Some(None);
let flat = nested.flatten();
assert_eq!(flat, None);
```

- inspect method takes ownership of the Option and applies the provided function to the contained value by reference if Some

```Rust
let opt = Some("hello");
let result = opt.inspect(|v| println!("Value is: {}", v));
assert_eq!(result, Some("hello")); // original value is preserved
```

- map transforms Option<T> to Option<U> by applying the provided function to the contained value of Some and leaving None values unchanged

```Rust
let opt = Some(3);
let mapped = opt.map(|x| x * 2);
assert_eq!(mapped, Some(6));

let none: Option<i32> = None;
let mapped = none.map(|x| x * 2);
assert_eq!(mapped, None);
```
