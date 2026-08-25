# College Event Platform Scope (MVP)

## 1) Product goal
Build a secure and deployable website for a college no-code hackathon that handles registration, team management, admin approvals, communication, and reporting.

## 2) User roles
- Participant (student)
  - Register and manage profile
  - Create/join a team
  - View application status and event updates
- Admin (organizer)
  - Review and approve/reject registrations
  - Manage event content and schedules
  - Export participant data and trigger notifications

## 3) Required pages
- Landing page (event overview)
- Rules & eligibility page
- Timeline page
- FAQ page
- Contact page
- Registration page
- Login page
- Participant dashboard
- Admin dashboard
- Admin review queue page

## 4) Registration data fields
- Participant details
  - Full name
  - College name
  - Email
  - Phone number
  - Course/year
- Team details
  - Team name
  - Team size
  - Team members (name + email)
- Hackathon inputs
  - Problem statement/theme preference
  - Prior project links (optional)
- Compliance
  - Terms acceptance
  - Privacy consent

## 5) Core workflow
1. Participant submits registration.
2. System validates fields and prevents duplicates.
3. Admin reviews pending entries.
4. Admin approves/rejects with reason.
5. System sends status notification by email.
6. Participant sees latest status on dashboard.

## 6) Notification requirements
- Registration received confirmation
- Approval notification
- Rejection notification with reason
- Event reminders (T-7 days, T-1 day, event day)
- Emergency organizer updates

## 7) Non-functional requirements
- Role-based authorization (participant/admin)
- Audit trail for admin actions
- Data export capability (CSV)
- Mobile-friendly UI
- Availability target during registration window
