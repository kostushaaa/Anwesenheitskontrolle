// Elemente aus dem DOM auswählen
const username = document.querySelector("#username").value;
const password = document.querySelector("#password").value;
const logbutton = document.querySelector(".login-btn");
const logform = document.querySelector("form");

// Eventlistener für das Formular
logform.addEventListener("submit", (event) => {
  event.preventDefault();

  // Benutzereingaben auslesen + trim
  const enteredUsername = username.value.trim();
  const enteredPassword = password.value.trim();

  // Prüfung: Sind die Eingaben korrekt?
  if (enteredUsername === "" || enteredPassword === "") {
    alert("Bitte Benutzername und Passwort eingeben!");
    return;
  }

  // Beispiel für eine einfache Login-Prüfung
  if (enteredUsername === "admin" && enteredPassword === "1234") {
    alert("Login erfolgreich! Willkommen, " + enteredUsername + "!");
    // optionales weiterleiten nach erfolgreichem Login
    window.location.href = "dashboard.html";
  } else {
    alert("Unültiger Benutzername oder Passwort.");
  }
});
