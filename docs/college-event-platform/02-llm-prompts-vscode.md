# LLM Prompt Pack for VS Code Implementation

Use one feature prompt at a time. Paste generated output into your VS Code project, then run tests before moving to the next feature.

## Prompt 1: Project bootstrap
"Generate a production-ready [framework] web app for a college hackathon platform. Include folder structure for frontend, backend API, config, tests, and deployment files. Add setup instructions and required environment variables in .env.example."

## Prompt 2: Auth + roles
"Add secure authentication with email/password and role-based access for participant and admin. Include password hashing, secure session/token handling, logout, and middleware to protect admin routes."

## Prompt 3: Registration form + API
"Create participant registration UI and backend API with strict server-side validation for required fields: name, college, email, phone, course/year, team details, consent. Reject invalid input and return structured errors."

## Prompt 4: Duplicate prevention
"Add duplicate checks for participant email, phone, and team name before registration is accepted. Return conflict error messages and test cases for duplicates."

## Prompt 5: Admin review flow
"Implement admin dashboard and registration review queue with approve/reject actions and rejection reason. Log reviewer, timestamp, and action history."

## Prompt 6: Notifications
"Add email notifications for registration received, approval, rejection, and reminders. Use template files and environment-based mail configuration."

## Prompt 7: Security hardening
"Add secure headers, strict CORS policy, rate limiting for public endpoints, CAPTCHA verification for registration endpoint, and centralized input sanitization."

## Prompt 8: Tests for each feature
"Generate unit and integration tests for the feature just added. Cover happy path, invalid input, unauthorized access, role misuse, and duplicate submissions."

## Prompt 9: Deployment artifacts
"Generate staging and production deployment configuration for [hosting platform], health check endpoint, logging, and rollback notes."

## Prompt 10: Root-cause bug fix style
"Given this error output, provide root-cause analysis and minimal patch only for the failing part. Do not rewrite unrelated files. Also provide updated tests for this fix."

---

## VS Code execution loop
1. Prompt for exactly one feature.
2. Paste code into correct files.
3. Run lint + tests.
4. Fix with root-cause prompt.
5. Commit small scoped change.
6. Repeat.
