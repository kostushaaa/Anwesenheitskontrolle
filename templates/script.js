// Sicherstellen, dass HTML vollständig geladen ist
document.addEventListener("DOMContentLoaded", () => {
  // Datum und Uhrzeit initialisieren und regelmäßig aktualisieren
  aktualisiereDatumUhrzeit();
  setInterval(aktualisiereDatumUhrzeit, 15000);

  // Benutzerliste rendern
  renderUserList();

  // Login-Formular verarbeiten
  initialisiereLoginForm();
});
//______________________________________________________
// Funktion, um das Datum und die Uhrzeit zu aktualisieren
function aktualisiereDatumUhrzeit() {
  const datumUhrzeitElement = document.getElementById('datum-uhrzeit');
  if (!datumUhrzeitElement) {
    console.error("Element mit der ID 'datum-uhrzeit' wurde nicht gefunden!");
    return;
  }

  const jetzt = new Date();

  // Formatieren: Wochentag, Datum, Uhrzeit
  const optionsDatum = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };
  const datum = jetzt.toLocaleDateString('de-DE', optionsDatum);
  const optionsUhrzeit = { hour: '2-digit', minute: '2-digit' };
  const uhrzeit = jetzt.toLocaleTimeString('de-DE', optionsUhrzeit);

  // Text in das Element einfügen
  datumUhrzeitElement.textContent = `Anwesendheit Fia26, heute ist der ${datum}, ${uhrzeit} Uhr`;

  // Debugging-Ausgabe
  console.log(`Generiertes Datum: ${datum}, Uhrzeit: ${uhrzeit} Uhr`);
}
//_____________________________________________________
// Beispiel-Benutzerdaten
const users = [
  {
    name: "Max Mustermann",
    email: "max.mustermann@example.com",
    loggedInAt: "2024-11-26 08:30",
    loggedOutAt: null,
    present: true, // Anwesenheit
  },
  {
    name: "Lisa Müller",
    email: "lisa.mueller@example.com",
    loggedInAt: "2024-11-26 09:00",
    loggedOutAt: null,
    present: false, // Abwesend
  },
];
//____________________________________________________
// HTML-Kacheln dynamisch erstellen
function createUserCard(user) {
  return `
      <div class="user-card">
          <h3>${user.name}</h3>
          <p>E-Mail: ${user.email}</p>
          <p>Eingeloggt am: ${user.loggedInAt || '-'}</p>
          <p>Ausgeloggt am: ${user.loggedOutAt || '-'}</p>
          <div class="attendance">
              <span class="${user.present ? 'present' : 'absent'}">
                  ${user.present ? '✔' : '✖'}
              </span>
              <p>${user.present ? 'Anwesend' : 'Abwesend'}</p>
          </div>
      </div>
  `;
}

// Nutzerdaten in die Benutzerliste einfügen
function renderUserList() {
  const userListContainer = document.querySelector('.user-list');
  if (!userListContainer) {
    console.error("Element mit der Klasse .user-list wurde nicht gefunden!");
    return;
  }

  userListContainer.innerHTML = users.map(createUserCard).join('');
}
//_____________________________________________________________
// Login-Formular verarbeiten
function initialisiereLoginForm() {
  const usernameElement = document.querySelector("#username");
  const passwordElement = document.querySelector("#password");
  const logform = document.querySelector("form");

  if (!usernameElement || !passwordElement || !logform) {
    console.error("Login-Formularelemente wurden nicht gefunden!");
    return;
  }

  logform.addEventListener("submit", (event) => {
    event.preventDefault();

    // Benutzername und Passwort auslesen und trimmen
    const enteredUsername = usernameElement.value.trim();
    const enteredPassword = passwordElement.value.trim();

    // Prüfung: Sind die Eingaben leer?
    if (enteredUsername === "" || enteredPassword === "") {
      alert("Bitte Benutzername und Passwort eingeben!");
      return;
    }

    // Beispiel für eine einfache Login-Prüfung
    if (enteredUsername === "admin" && enteredPassword === "1234") {
      alert(`Login erfolgreich! Willkommen, ${enteredUsername}!`);
      window.location.href = "dashboard.html"; // Weiterleitung nach Login
    } else {
      alert("Ungültiger Benutzername oder Passwort.");
    }
  });
}